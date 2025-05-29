#pragma once

#include "widget.hpp"

namespace uva
{
    namespace widgets
    {
        class input : public widget {
        protected:
            std::string content;
        public:
            void render(void* target) override;
            void parse(void* target, uva::xml::schema& schema, uva::xml& xml) override;
            uva::size calculate_min_size() override;
            bool on_char(std::string c) override;
        };
    };
};
