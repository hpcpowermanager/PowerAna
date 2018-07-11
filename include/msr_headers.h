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
 * 	Sharda Dixit <sharda@cdac.in>
 * *********************************************************************** */

#ifndef MSR_HEADERS_H_
#define MSR_HEADERS_H_

#define MSR_RAPL_POWER_UNIT     0x606

#define MSR_PKG_ENERGY_STATUS   0x611
#define MSR_PP0_ENERGY_STATUS   0x639
#define MSR_DRAM_ENERGY_STATUS  0x619

#define MSR_TSC                 0x10

#define MSR_PKG_C2_RESIDENCY    0x60D
#define MSR_PKG_C3_RESIDENCY    0x3F8
#define MSR_PKG_C6_RESIDENCY    0x3F9
#define MSR_PKG_C7_RESIDENCY    0x3FA

#define MSR_CORE_C3_RESIDENCY   0x3FC
#define MSR_CORE_C6_RESIDENCY   0x3FD
#define MSR_CORE_C7_RESIDENCY   0x3FE

#endif  // MSR_HEADERS_H_
