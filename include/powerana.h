/* **********************************************************************
 * Copyright 2018, C-DAC.
 * All Rights Reserved.
 *
 * PowerAna is a free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * PowerAna is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Authors:
 *      Sharda Dixit <sharda@cdac.in>
 * *********************************************************************** */

#ifndef POWERANA_H_
#define POWERANA_H_

#include <node.h>

#include <sys/time.h>

class PowerAna {
 public:
    int init();
    int loop();
    void cleanup();
    void update_counters();
    void update_timestamp();
    void print_headers();
    void print_counters();
    void print_timestamp();

 private:
    timeval stamp_before, stamp_after, stamp_delta;
    Node node;
};

#endif  // POWERANA_H_
