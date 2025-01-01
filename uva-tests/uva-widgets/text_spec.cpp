#include <iostream>

#include <uva/widgets/text.hpp>

#include <uva/file.hpp>
#include <uva/drawing/image.hpp>
#include <uva/xml.hpp>

#include <uva/tests.hpp>

using namespace uva::tests;

describe of(structure, "uva::widgets::layout", []() {
    it("should set w, h correctly", [](){
        uva::drawing::memory_surface surface({400,400});
        uva::drawing::software_renderer renderer(surface);

        uva::widgets::text t("Hello, World!", renderer);

        expect(t.w).to<eq>(74);
        expect(t.h).to<eq>(11);
    });
    it("rendering simple text", [](){
        uva::drawing::memory_surface surface({400,400});
        uva::drawing::software_renderer renderer(surface);

        renderer.clear(uva::color(255, 255, 255, 255));

        uva::widgets::text t("Hello, World!", renderer);

        t.render(renderer);

        uva::drawing::image img = surface.to_image();

        img.save_bitmap("test.bmp");
    });
});