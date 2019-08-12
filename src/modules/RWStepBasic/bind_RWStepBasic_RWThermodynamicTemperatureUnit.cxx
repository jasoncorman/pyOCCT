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
#include <Standard.hxx>
#include <Standard_Handle.hxx>
#include <StepData_StepReaderData.hxx>
#include <Standard_TypeDef.hxx>
#include <Interface_Check.hxx>
#include <StepBasic_ThermodynamicTemperatureUnit.hxx>
#include <StepData_StepWriter.hxx>
#include <Interface_EntityIterator.hxx>
#include <RWStepBasic_RWThermodynamicTemperatureUnit.hxx>

void bind_RWStepBasic_RWThermodynamicTemperatureUnit(py::module &mod){

py::class_<RWStepBasic_RWThermodynamicTemperatureUnit, std::unique_ptr<RWStepBasic_RWThermodynamicTemperatureUnit, Deleter<RWStepBasic_RWThermodynamicTemperatureUnit>>> cls_RWStepBasic_RWThermodynamicTemperatureUnit(mod, "RWStepBasic_RWThermodynamicTemperatureUnit", "Read & Write tool for ThermodynamicTemperatureUnit");

// Constructors
cls_RWStepBasic_RWThermodynamicTemperatureUnit.def(py::init<>());

// Fields

// Methods
// cls_RWStepBasic_RWThermodynamicTemperatureUnit.def_static("operator new_", (void * (*)(size_t)) &RWStepBasic_RWThermodynamicTemperatureUnit::operator new, "None", py::arg("theSize"));
// cls_RWStepBasic_RWThermodynamicTemperatureUnit.def_static("operator delete_", (void (*)(void *)) &RWStepBasic_RWThermodynamicTemperatureUnit::operator delete, "None", py::arg("theAddress"));
// cls_RWStepBasic_RWThermodynamicTemperatureUnit.def_static("operator new[]_", (void * (*)(size_t)) &RWStepBasic_RWThermodynamicTemperatureUnit::operator new[], "None", py::arg("theSize"));
// cls_RWStepBasic_RWThermodynamicTemperatureUnit.def_static("operator delete[]_", (void (*)(void *)) &RWStepBasic_RWThermodynamicTemperatureUnit::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepBasic_RWThermodynamicTemperatureUnit.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepBasic_RWThermodynamicTemperatureUnit::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepBasic_RWThermodynamicTemperatureUnit.def_static("operator delete_", (void (*)(void *, void *)) &RWStepBasic_RWThermodynamicTemperatureUnit::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepBasic_RWThermodynamicTemperatureUnit.def("ReadStep", (void (RWStepBasic_RWThermodynamicTemperatureUnit::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepBasic_ThermodynamicTemperatureUnit> &) const) &RWStepBasic_RWThermodynamicTemperatureUnit::ReadStep, "Reads ThermodynamicTemperatureUnit", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepBasic_RWThermodynamicTemperatureUnit.def("WriteStep", (void (RWStepBasic_RWThermodynamicTemperatureUnit::*)(StepData_StepWriter &, const opencascade::handle<StepBasic_ThermodynamicTemperatureUnit> &) const) &RWStepBasic_RWThermodynamicTemperatureUnit::WriteStep, "Writes ThermodynamicTemperatureUnit", py::arg("SW"), py::arg("ent"));
cls_RWStepBasic_RWThermodynamicTemperatureUnit.def("Share", (void (RWStepBasic_RWThermodynamicTemperatureUnit::*)(const opencascade::handle<StepBasic_ThermodynamicTemperatureUnit> &, Interface_EntityIterator &) const) &RWStepBasic_RWThermodynamicTemperatureUnit::Share, "Fills data for graph (shared items)", py::arg("ent"), py::arg("iter"));

// Enums

}