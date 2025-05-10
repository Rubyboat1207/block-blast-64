/**
 * @file timer_manager.cpp
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 * 
 * Copyright (C) 2025 Rubyboat (owner of https://github.com/Rubyboat1207)
 */

#include "timer_manager.hpp"


void TimerManager::begin_timeout(float seconds, void (*user)(TimerUser *))
{
    timer = new_timer_context(TIMER_TICKS(seconds * 1000000), TF_CONTINUOUS, [](int ovfl, void *ctx) {
        TimerUser *user = (TimerUser *)ctx;
        user->on_timeout();
    }, (void *)user);
}

void TimerManager::stop_timeout()
{
    stop_timer(timer);
    timer = nullptr;
}

void TimerManager::begin_timeout(float seconds)
{
    if(user == nullptr)
    {
        return;
    }
    timer = new_timer_context(TIMER_TICKS(seconds * 1000000), TF_CONTINUOUS, [](int ovfl, void *ctx) {
        TimerUser *user = (TimerUser *)ctx;
        user->on_timeout();
    }, (void *)user);
}

void TimerManager::bind_user(TimerUser *user)
{
    this->user = user;
}
