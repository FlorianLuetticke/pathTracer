#include <random>

#include "math/ray.h"
#include "primitives/sphere.h"
#include "scene/camera.h"
#include "scene/scene.h"

int main() {
    TScene scene;
    std::mt19937 generator;
    std::uniform_real_distribution<double> distribution(-0.5, 0.5);
    scene.add(TSphere(20, TPoint(35, 8, 0)));
    scene.add(TSphere(3, TPoint(17, 8, 8)));
    scene.add(TSphere(3, TPoint(17, -8, 8)));
    scene.add(TSphere(3, TPoint(17, 8, -8)));
    scene.add(TSphere(3, TPoint(17, -8, -8)));

    TCamera cam(300, 400, 18.);
    TCamera cam2(300, 400, 18.);
    size_t nSamples = 100;

    for (size_t row = 0; row < cam.rows(); ++row) {
        for (size_t col = 0; col < cam.columns(); ++col) {
            for (size_t sample = 0; sample < nSamples; ++sample) {
                auto ray = cam.castRay(row, col, distribution(generator),
                                       distribution(generator));
                auto optHit = scene.findHit(ray);
                if (optHit) {
                    auto distance =
                        (optHit->intersection - TPoint(0, 0, 0)).norm() - 16.;
                    cam.colorAt(row, col) +=
                        // sColor{distance, distance, distance};
                        sColor{1 + optHit->normal.x(), 1 + optHit->normal.y(),
                               1 + optHit->normal.z()};
                    cam2.colorAt(row, col) +=
                        sColor{distance, distance, distance};
                    // std::cout << row << ", " << col << ": " << optHit->normal
                    //           << " " << optHit->intersection << " distance "
                    //           << (optHit->intersection - TPoint(0, 0,
                    //           0)).norm()
                    //           << std::endl;
                }
            }
        }
    }
    cam.picture().savePNG("test.png");
    cam2.picture().savePNG("test2.png");
}