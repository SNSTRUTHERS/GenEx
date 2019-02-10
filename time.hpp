#ifndef TIME_HPP
#define TIME_HPP

#include "base.hpp"

namespace GenEx {
    namespace Time {
            /** \brief Returns the current time in seconds with nanosecond accuracy if possible.
         *
         * \return double Current time in seconds
         */
        double GetSecs() {
            return std::chrono::duration_cast<std::chrono::nanoseconds>(
                       std::chrono::high_resolution_clock::now().time_since_epoch()).count() /
                   1000000000.0;
        }

        class Timer {
        private:
            double mStart;
        public:
            Timer() {
                reset();
            }

            void reset() {
                mStart = GetSecs();
            }

            double get_duration() {
                return GetSecs() - mStart;
            }
        };
    }
}

#endif // TIME_HPP
