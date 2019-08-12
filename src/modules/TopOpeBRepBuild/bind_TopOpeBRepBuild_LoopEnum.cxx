/*
This file is part of pyOCCT which provides Python bindings to the OpenCASCADE
geometry kernel.

Copyright (C) 2016-2018  Laughlin Research, LLC
Copyright (C) 2019 Trevor Laughlin and the pyOCCT contributors

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include <pyOCCT_Common.hxx>
#include <TopOpeBRepBuild_LoopEnum.hxx>

void bind_TopOpeBRepBuild_LoopEnum(py::module &mod){

py::enum_<TopOpeBRepBuild_LoopEnum>(mod, "TopOpeBRepBuild_LoopEnum", "None")
	.value("TopOpeBRepBuild_ANYLOOP", TopOpeBRepBuild_LoopEnum::TopOpeBRepBuild_ANYLOOP)
	.value("TopOpeBRepBuild_BOUNDARY", TopOpeBRepBuild_LoopEnum::TopOpeBRepBuild_BOUNDARY)
	.value("TopOpeBRepBuild_BLOCK", TopOpeBRepBuild_LoopEnum::TopOpeBRepBuild_BLOCK)
	.export_values();


}