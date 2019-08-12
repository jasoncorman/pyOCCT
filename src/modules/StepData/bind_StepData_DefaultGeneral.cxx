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
#include <StepData_GeneralModule.hxx>
#include <Standard_TypeDef.hxx>
#include <Standard_Handle.hxx>
#include <Standard_Transient.hxx>
#include <Interface_EntityIterator.hxx>
#include <Interface_ShareTool.hxx>
#include <Interface_Check.hxx>
#include <Interface_CopyTool.hxx>
#include <StepData_DefaultGeneral.hxx>
#include <Standard_Type.hxx>

void bind_StepData_DefaultGeneral(py::module &mod){

py::class_<StepData_DefaultGeneral, opencascade::handle<StepData_DefaultGeneral>, StepData_GeneralModule> cls_StepData_DefaultGeneral(mod, "StepData_DefaultGeneral", "DefaultGeneral defines a GeneralModule which processes Unknown Entity from StepData only");

// Constructors
cls_StepData_DefaultGeneral.def(py::init<>());

// Fields

// Methods
cls_StepData_DefaultGeneral.def("FillSharedCase", (void (StepData_DefaultGeneral::*)(const Standard_Integer, const opencascade::handle<Standard_Transient> &, Interface_EntityIterator &) const) &StepData_DefaultGeneral::FillSharedCase, "Specific filling of the list of Entities shared by an Entity <ent>, which is an UnknownEntity from StepData.", py::arg("casenum"), py::arg("ent"), py::arg("iter"));
cls_StepData_DefaultGeneral.def("CheckCase", (void (StepData_DefaultGeneral::*)(const Standard_Integer, const opencascade::handle<Standard_Transient> &, const Interface_ShareTool &, opencascade::handle<Interface_Check> &) const) &StepData_DefaultGeneral::CheckCase, "Specific Checking of an Entity <ent>", py::arg("casenum"), py::arg("ent"), py::arg("shares"), py::arg("ach"));
cls_StepData_DefaultGeneral.def("NewVoid", (Standard_Boolean (StepData_DefaultGeneral::*)(const Standard_Integer, opencascade::handle<Standard_Transient> &) const) &StepData_DefaultGeneral::NewVoid, "Specific creation of a new void entity", py::arg("CN"), py::arg("entto"));
cls_StepData_DefaultGeneral.def("CopyCase", (void (StepData_DefaultGeneral::*)(const Standard_Integer, const opencascade::handle<Standard_Transient> &, const opencascade::handle<Standard_Transient> &, Interface_CopyTool &) const) &StepData_DefaultGeneral::CopyCase, "Specific Copy ('Deep') from <entfrom> to <entto> (same type) by using a CopyTool which provides its working Map. Use method Transferred from TransferControl to work", py::arg("casenum"), py::arg("entfrom"), py::arg("entto"), py::arg("TC"));
cls_StepData_DefaultGeneral.def_static("get_type_name_", (const char * (*)()) &StepData_DefaultGeneral::get_type_name, "None");
cls_StepData_DefaultGeneral.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepData_DefaultGeneral::get_type_descriptor, "None");
cls_StepData_DefaultGeneral.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepData_DefaultGeneral::*)() const) &StepData_DefaultGeneral::DynamicType, "None");

// Enums

}