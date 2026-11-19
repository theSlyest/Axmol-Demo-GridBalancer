#pragma once

#include <array>

#include "2d/DrawNode.h"
#include "2d/Label.h"
#include "2d/Scene.h"
#include "BalancerValue.h"
#include "BalancerGenerator.h"
#include "BalancerChart.h"

class BalancerScene : public ax::Scene
{
public:
    bool init() override;
    
    // implement the "static create()" method manually
    CREATE_FUNC(BalancerScene);

    void update(float dt) override;

private:
    const float UI_OFFSET = 32.0f;
    
    const int STRIKES = 3;

    struct GeneratorSpec
    {
        std::string name;
        ax::Color4F color;
        float rate; // how fast the bar moves toward its target, in full ranges per second
    };

    const std::array<GeneratorSpec, 3> GENERATORS = {{
        { "FAST",   ax::Color4F(0.4f, 1.0f, 0.4f, 1.0f), 0.5f },
        { "MEDIUM", ax::Color4F(0.2f, 0.6f, 1.0f, 1.0f), 0.25f },
        { "SLOW",   ax::Color4F(1.0f, 0.2f, 1.0f, 1.0f), 0.125f }
    }};
    const float GEN_START = 0.5f;
    const float TOLERANCE = 0.1f;
    const float GRACE_PERIOD = 4.0f;
    const char* BEST_KEY = "Best";

    int _strikes = 0;
    float _downTime = 0.0f;
    float _upTime = 0.0f;
    int _best = 0;

    BalancerValue* _upTimeUi = nullptr;
    BalancerValue* _strikesUi = nullptr;
    BalancerValue* _bestUi = nullptr;

    std::vector<BalancerGenerator*> _gens;

    BalancerChart* _chart = nullptr;

    ax::DrawNode* _endLayer = nullptr;
    ax::Label* _upTimeLbl = nullptr;
    ax::Label* _bestLbl = nullptr;

    void setUpTime(float upTime);
    void setStrikes(int strikes);
    void setBest(int best);

    void initGenerators(const ax::Vec2& size, const ax::Vec2& origin);
    void initEndLayer(const ax::Vec2& size, const ax::Vec2& origin);

    void gameOver();
    void reset();
};
