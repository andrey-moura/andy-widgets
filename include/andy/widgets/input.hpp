#pragma once

#include "widget.hpp"

namespace andy
{
    namespace widgets
    {
        class input : public widget {
        protected:
            std::string content;
        public:
            void render(void* target) override;
            void parse(void* target, andy::xml::schema& schema, andy::xml& xml) override;
            andy::size calculate_min_size() override;
            bool on_char(std::string c) override;
        };
    };
};
