#include "robotsim.h"
#include "robotdiag.h"
#include <thread>
#include <vector>
#include <atomic>
#include <cstdlib>
#include <cmath>

using namespace robotsim;

namespace {
    struct Motor
    {
        int id;
        int delay;
    };

    bool run_;

    std::atomic<int> event_sum_;

    void sim_loop(const Motor& new_motor)
    {
        Motor motor = new_motor;

        int produced = 0;

        float t  = 0.0;
        float td = float(motor.delay) / 1000.0;
        while (run_)
        {
            // Sinus simple pour simuler la position.
            float p = 0.5 * sin(float(motor.delay/10) * t);
            t += td;

            robotdiag::RobotState evt;
            evt.id      = motor.id;
            evt.t       = t;
            evt.cur_pos = p;
            robotdiag::push_event(evt);

            produced++;
            std::this_thread::sleep_for(std::chrono::milliseconds(motor.delay));
        }

        printf("Motor %d produced %d event(s)\n", motor.id, produced);
        event_sum_.fetch_add(produced);

    }

    std::vector<std::thread> threads_;
}

void robotsim::init(int n_motors, int delay = 10, int d_delta = 3)
{
    run_ = true;
    event_sum_.store(0);

    for (int i = 1; i <= n_motors; ++i) {
        Motor m = {i, delay + (rand() % (2*d_delta + 1) - d_delta)};
        threads_.push_back(std::thread(sim_loop, m)); 
    }
}

void robotsim::stop_and_join()
{
    run_ = false;
    for (auto i = threads_.begin(); i != threads_.end(); ++i) {
        i->join();
    }

    printf("Total events produced: %d\n", event_sum_.load());
}

