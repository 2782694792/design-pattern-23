#include <string>
#include <iostream>

class IState;

// 上下文处理类
class IContext
{
public:
    enum class ActionType // 处理信号
    {
        Use,
        Alarm,
        Phone
    };

    virtual ~IContext() {}
    
    virtual void doAction(ActionType actionType) = 0; // 指定信号
    virtual void setClock(int hour) = 0;
    virtual void stateChange(IState *state) = 0; // 状态更改
    virtual void callSecurityCenter(const std::string &msg) = 0;
    virtual void recoderLog(const std::string &msg) = 0;
};

// 具体的上下文处理类
class SafeFrame : public IContext
{
public:
    SafeFrame();
    virtual void setClock(int hour) override;
    virtual void doAction(ActionType actionType) override;
    virtual void stateChange(IState *state) override;
    virtual void callSecurityCenter(const std::string &msg) override;
    virtual void recoderLog(const std::string &msg) override;

private:
    IState *m_state; // 包含一个表达自身的状态指针
};

// 抽象状态，包含状态对应事件处理
class IState
{
public:
    virtual ~IState() {}
    virtual void doColock(IContext *ctx, int hour) = 0;
    virtual void doUse(IContext *ctx) = 0;
    virtual void doAlarm(IContext *ctx) = 0;
    virtual void doPhone(IContext *ctx) = 0;
};


class DayState : public IState
{
public:
    static DayState &GetInstance()
    {
        static DayState s;
        return s;
    }
    virtual void doColock(IContext *ctx, int hour) override;
    virtual void doUse(IContext *ctx) override
    {
        ctx->recoderLog("Day use ");
    }
    virtual void doAlarm(IContext *ctx) override
    {
        ctx->callSecurityCenter("Day alarm");
    }
    virtual void doPhone(IContext *ctx) override
    {
        ctx->callSecurityCenter("Day phone");
    }

    ~DayState() = default;

    DayState(const DayState &) = delete;
    DayState(DayState &&) = delete;
    DayState &operator=(const DayState &) = delete;
    DayState &operator=(DayState &&) = delete;

protected:
    DayState() {}
};

class NightState : public IState
{
public:
    static NightState &GetInstance()
    {
        static NightState s;
        return s;
    }
    virtual void doColock(IContext *ctx, int hour) override;
    virtual void doUse(IContext *ctx) override
    {
        ctx->callSecurityCenter("Night use ");
    }
    virtual void doAlarm(IContext *ctx) override
    {
        ctx->callSecurityCenter("Night alarm");
    }
    virtual void doPhone(IContext *ctx) override
    {
        ctx->recoderLog("Night phone");
    }

    ~NightState() = default;

    NightState(const NightState &) = delete;
    NightState(NightState &&) = delete;
    NightState &operator=(const NightState &) = delete;
    NightState &operator=(NightState &&) = delete;

protected:
    NightState() {}
};

void DayState::doColock(IContext *ctx, int hour)
{
    if (hour < 9 || 17 <= hour)
    {
        ctx->stateChange(&NightState::GetInstance());
    }
}

void NightState::doColock(IContext *ctx, int hour)
{
    if (9 <= hour || hour < 17)
    {
        ctx->stateChange(&DayState::GetInstance());
    }
}

SafeFrame::SafeFrame() : m_state(&DayState::GetInstance()) {}

void SafeFrame::setClock(int hour)
{
    std::cout << "now timw is " << hour << std::endl;
    m_state->doColock(this, hour);
}

void SafeFrame::doAction(ActionType actionType)
{
    switch (actionType)
    {
        case ActionType::Alarm:
            m_state->doAlarm(this);
            break;
        case ActionType::Phone:
            m_state->doPhone(this);
            break;
        case ActionType::Use:
        default:
            m_state->doUse(this);
            break;
    }
}

void SafeFrame::stateChange(IState *state)
{
    std::cout << __FUNCTION__ << std::endl;
    m_state = state;
}

void SafeFrame::callSecurityCenter(const std::string &msg)
{
    std::cout << __FUNCTION__ << " " << msg << std::endl;
}

void SafeFrame::recoderLog(const std::string &msg)
{
    std::cout << __FUNCTION__ << " " << msg << std::endl;
}

int main()
{
    IContext *ctx = new SafeFrame;
    for (int i = 0; i < 24; ++i)
    {
        ctx->setClock(i);
        ctx->doAction(IContext::ActionType::Use);
        ctx->doAction(IContext::ActionType::Phone);
        ctx->doAction(IContext::ActionType::Alarm);
    }
    delete ctx;
    return 0;
}