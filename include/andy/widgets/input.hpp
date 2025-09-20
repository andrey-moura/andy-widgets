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
            void render(andy::drawing::basic_renderer& renderer) override;
            void parse(andy::xml::schema& schema, andy::xml& xml) override;
            andy::size calculate_min_size(andy::drawing::basic_renderer& renderer) override;
            bool on_char(char c) override;
        };
    };
};
