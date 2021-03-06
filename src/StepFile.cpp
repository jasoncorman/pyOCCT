/*
This file is part of pyOCCT which provides Python bindings to the OpenCASCADE
geometry kernel.

Copyright (C) 2016-2018  Laughlin Research, LLC (info@laughlinresearch.com)

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
#include <pyOCCT_Common.hpp>

#include <StepFile_Read.hxx>
#include <Standard_TypeDef.hxx>
#include <Standard_Handle.hxx>
#include <StepData_StepModel.hxx>
#include <StepData_Protocol.hxx>

PYBIND11_MODULE(StepFile, mod) {

	// IMPORT
	py::module::import("OCCT.Standard");
	py::module::import("OCCT.StepData");

	py::module other_mod;

	// IMPORT GUARDS

	// ENUMS

	// FUNCTIONS
	// C:\Miniconda\envs\occt\Library\include\opencascade\StepFile_Read.hxx
	mod.def("StepFile_ReadTrace", (void (*)(const Standard_Integer)) &StepFile_ReadTrace, "None", py::arg("mode"));

	// C:\Miniconda\envs\occt\Library\include\opencascade\StepFile_Read.hxx
	mod.def("StepFile_Read", (Standard_Integer (*)(char *, const opencascade::handle<StepData_StepModel> &, const opencascade::handle<StepData_Protocol> &)) &StepFile_Read, "None", py::arg("nomfic"), py::arg("stepmodel"), py::arg("protocol"));


	// CLASSES

}
