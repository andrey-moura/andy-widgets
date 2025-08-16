#include <iostream>

#include <andy/widgets/text.hpp>

#include <andy/file.hpp>
#include <andy/drawing/image.hpp>
#include <andy/xml.hpp>

#include <andy/tests.hpp>

using namespace andy::tests;

describe of(structure, "andy::widgets::layout", []() {
    it("should set w, h correctly", [](){
        andy::drawing::memory_surface surface({400,400});
        andy::drawing::software_renderer renderer(surface);

        andy::widgets::text t("Hello, World!", renderer);

        expect(t.w).to<eq>(74);
        expect(t.h).to<eq>(11);
    });
    it("rendering simple text", [](){
        andy::drawing::memory_surface surface({400,400});
        andy::drawing::software_renderer renderer(surface);

        renderer.clear(andy::color(255, 255, 255, 255));

        andy::widgets::text t("Hello, World!", renderer);

        t.render(renderer);

        andy::drawing::image img = surface.to_image();

        img.save_bitmap("test.bmp");
    });
});