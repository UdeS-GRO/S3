#include "robotdiag.h"
#include "robotsim.h"
#include <signal.h>
#include <unistd.h>

namespace {
    bool run_;

}

void sighandler(int)
{
    run_ = false;
}

int main(int argc, char** argv)
{
    run_ = true;

    signal(SIGINT, sighandler);

    robotdiag::init();

    while (run_) {
        pause();
    }

    robotdiag::stop_and_join();

    return 0;
}
