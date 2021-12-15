#pragma once

#include "Actions.hpp"


class ActionBuilderBase
{
    protected:
        Action &action;
    public:
        ActionBuilderBase(Action &action);
};

class ActionBuilder : public ActionBuilderBase
{
    private:
        Action action;
    public:
        ActionBuilder();
};