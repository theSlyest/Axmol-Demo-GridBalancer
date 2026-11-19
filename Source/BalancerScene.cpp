#include "BalancerScene.h"

#include "Director.h"

USING_NS_AX;

// on "init" you need to initialize your instance
bool BalancerScene::init()
{
    if (!Scene::init())
        return false;

    const auto& size = _director->getVisibleSize();
    const Vec2& origin = _director->getVisibleOrigin();

    // HUD
    _hud = BalancerHud::create(size);
    _hud->setPosition(origin);
    _hud->setBest(_best.get());
    addChild(_hud);

    // GAME
    initGame();

    // GENERATORS
    initGenerators(size, origin);

    // CHART
    _chart = BalancerChart::create(_game->getTolerance());
    _chart->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
    _chart->setPosition(origin.x + size.width / 2.0f, origin.y + _hud->getBottom() - 3.0f * UI_OFFSET);
    addChild(_chart);

    // GAME OVER LAYER
    initEndLayer(size, origin);

    reset();

    return true;
}

void BalancerScene::update(const float dt)
{
    _game->update(dt);

    for (size_t i = 0; i < _gens.size(); ++i)
        _gens[i]->setValue(_game->getGeneratorValue(i));

    _chart->update(dt, _game->getDemand(), _game->getSupply());
}

void BalancerScene::initGame()
{
    BalancerGame::Config config;
    for (const auto& generator : GENERATORS)
        config.generatorRates.push_back(generator.rate);

    _game = std::make_unique<BalancerGame>(config);
    _game->onUpTimeChanged = [this](const float upTime) { _hud->setUpTime(upTime); };
    _game->onStrikesChanged = [this](const int strikes) { _hud->setStrikes(strikes); };
    _game->onGraceChanged = [this](const bool active, const float time) {
        if (active)
            _chart->setGraceTime(time);
        _chart->setGraceVisible(active);
    };
    _game->onGameOver = [this] { gameOver(); };
}

void BalancerScene::initGenerators(const Vec2& size, const Vec2& origin)
{
    const auto count = static_cast<float>(GENERATORS.size());
    const float first = origin.x + size.width / 2.0f - (count - 1.0f) * GENERATOR_SPACING / 2.0f;
    for (size_t i = 0; i < GENERATORS.size(); ++i) {
        const auto& spec = GENERATORS[i];
        const auto gen = BalancerGenerator::create(spec.color, spec.name);
        gen->onIncrease = [this, i] { _game->increase(i); };
        gen->onDecrease = [this, i] { _game->decrease(i); };
        gen->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
        gen->setPosition(first + static_cast<float>(i) * GENERATOR_SPACING, UI_OFFSET);
        addChild(gen);
        _gens.push_back(gen);
    }
}

void BalancerScene::initEndLayer(const Vec2 &size, const Vec2 &origin)
{
    _endLayer = BalancerGameOverLayer::create();
    _endLayer->setPosition(origin + (size - Vec2(_endLayer->getContentSize())) / 2.0f);
    _endLayer->onPlayAgain = [this] { reset(); };
    addChild(_endLayer, 1);
}

void BalancerScene::gameOver()
{
    unscheduleUpdate();

    const int upTime = static_cast<int>(_game->getUpTime());
    if (_best.submit(upTime))
        _hud->setBest(_best.get());

    _endLayer->show(upTime, _best.get());
}

void BalancerScene::reset()
{
    _game->reset();
    _chart->reset(_game->getDemand());
    for (size_t i = 0; i < _gens.size(); ++i)
        _gens[i]->setValue(_game->getGeneratorValue(i));

    _endLayer->hide();
    scheduleUpdate();
}
