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
#include <TopoDS_TShape.hxx>
#include <TopAbs_ShapeEnum.hxx>
#include <Standard_Handle.hxx>
#include <TopoDS_TCompSolid.hxx>
#include <Standard_Type.hxx>

void bind_TopoDS_TCompSolid(py::module &mod){

py::class_<TopoDS_TCompSolid, opencascade::handle<TopoDS_TCompSolid>, TopoDS_TShape> cls_TopoDS_TCompSolid(mod, "TopoDS_TCompSolid", "A set of solids connected by their faces.");

// Constructors
cls_TopoDS_TCompSolid.def(py::init<>());

// Fields

// Methods
cls_TopoDS_TCompSolid.def("ShapeType", (TopAbs_ShapeEnum (TopoDS_TCompSolid::*)() const) &TopoDS_TCompSolid::ShapeType, "returns COMPSOLID");
cls_TopoDS_TCompSolid.def("EmptyCopy", (opencascade::handle<TopoDS_TShape> (TopoDS_TCompSolid::*)() const) &TopoDS_TCompSolid::EmptyCopy, "Returns an empty TCompSolid.");
cls_TopoDS_TCompSolid.def_static("get_type_name_", (const char * (*)()) &TopoDS_TCompSolid::get_type_name, "None");
cls_TopoDS_TCompSolid.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &TopoDS_TCompSolid::get_type_descriptor, "None");
cls_TopoDS_TCompSolid.def("DynamicType", (const opencascade::handle<Standard_Type> & (TopoDS_TCompSolid::*)() const) &TopoDS_TCompSolid::DynamicType, "None");

// Enums

}