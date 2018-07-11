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

#ifndef NODE_H_
#define NODE_H_

#include <core.h>
#include <pkg.h>
#include <procstat.h>

#include <string>
#include <vector>

class Node {
 public:
    std::vector<Pkg> pkgs;
    ProcStat procstat;
    std::string get_node_name();
    void init();
    void find_topology();
    void update(timeval stamp_delta);

 private:
    std::string node_name;
};

#endif  // NODE_H_
