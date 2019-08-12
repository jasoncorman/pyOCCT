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
#include <StepData_SelectReal.hxx>
#include <Standard_TypeDef.hxx>
#include <Standard_Handle.hxx>
#include <StepGeom_TrimmingMember.hxx>
#include <Standard_Type.hxx>

void bind_StepGeom_TrimmingMember(py::module &mod){

py::class_<StepGeom_TrimmingMember, opencascade::handle<StepGeom_TrimmingMember>, StepData_SelectReal> cls_StepGeom_TrimmingMember(mod, "StepGeom_TrimmingMember", "For immediate members of TrimmingSelect, i.e. : ParameterValue (a Real)");

// Constructors
cls_StepGeom_TrimmingMember.def(py::init<>());

// Fields

// Methods
cls_StepGeom_TrimmingMember.def("HasName", (Standard_Boolean (StepGeom_TrimmingMember::*)() const) &StepGeom_TrimmingMember::HasName, "None");
cls_StepGeom_TrimmingMember.def("Name", (Standard_CString (StepGeom_TrimmingMember::*)() const) &StepGeom_TrimmingMember::Name, "None");
cls_StepGeom_TrimmingMember.def("SetName", (Standard_Boolean (StepGeom_TrimmingMember::*)(const Standard_CString)) &StepGeom_TrimmingMember::SetName, "None", py::arg("name"));
cls_StepGeom_TrimmingMember.def_static("get_type_name_", (const char * (*)()) &StepGeom_TrimmingMember::get_type_name, "None");
cls_StepGeom_TrimmingMember.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &StepGeom_TrimmingMember::get_type_descriptor, "None");
cls_StepGeom_TrimmingMember.def("DynamicType", (const opencascade::handle<Standard_Type> & (StepGeom_TrimmingMember::*)() const) &StepGeom_TrimmingMember::DynamicType, "None");

// Enums

}