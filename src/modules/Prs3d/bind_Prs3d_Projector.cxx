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
#include <Standard_Transient.hxx>
#include <HLRAlgo_Projector.hxx>
#include <Standard_TypeDef.hxx>
#include <Standard_Handle.hxx>
#include <Prs3d_Projector.hxx>
#include <Standard_Type.hxx>

void bind_Prs3d_Projector(py::module &mod){

py::class_<Prs3d_Projector, opencascade::handle<Prs3d_Projector>, Standard_Transient> cls_Prs3d_Projector(mod, "Prs3d_Projector", "A projector object. This object defines the parameters of a view for a visualization algorithm. It is, for example, used by the hidden line removal algorithms.");

// Constructors
cls_Prs3d_Projector.def(py::init<const HLRAlgo_Projector &>(), py::arg("Pr"));
cls_Prs3d_Projector.def(py::init<const Standard_Boolean, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real>(), py::arg("Pers"), py::arg("Focus"), py::arg("DX"), py::arg("DY"), py::arg("DZ"), py::arg("XAt"), py::arg("YAt"), py::arg("ZAt"), py::arg("XUp"), py::arg("YUp"), py::arg("ZUp"));

// Fields

// Methods
cls_Prs3d_Projector.def("Projector", (HLRAlgo_Projector (Prs3d_Projector::*)() const) &Prs3d_Projector::Projector, "Returns a projector object for use in a hidden line removal algorithm.");
cls_Prs3d_Projector.def_static("get_type_name_", (const char * (*)()) &Prs3d_Projector::get_type_name, "None");
cls_Prs3d_Projector.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &Prs3d_Projector::get_type_descriptor, "None");
cls_Prs3d_Projector.def("DynamicType", (const opencascade::handle<Standard_Type> & (Prs3d_Projector::*)() const) &Prs3d_Projector::DynamicType, "None");

// Enums

}