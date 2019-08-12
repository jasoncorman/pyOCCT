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
#include <StepToTopoDS_Root.hxx>
#include <Standard.hxx>
#include <Standard_Handle.hxx>
#include <StepShape_FaceSurface.hxx>
#include <StepToTopoDS_Tool.hxx>
#include <StepToTopoDS_NMTool.hxx>
#include <TopoDS_Shape.hxx>
#include <StepToTopoDS_TranslateFaceError.hxx>
#include <StepToTopoDS_TranslateFace.hxx>

void bind_StepToTopoDS_TranslateFace(py::module &mod){

py::class_<StepToTopoDS_TranslateFace, std::unique_ptr<StepToTopoDS_TranslateFace, Deleter<StepToTopoDS_TranslateFace>>, StepToTopoDS_Root> cls_StepToTopoDS_TranslateFace(mod, "StepToTopoDS_TranslateFace", "None");

// Constructors
cls_StepToTopoDS_TranslateFace.def(py::init<>());
cls_StepToTopoDS_TranslateFace.def(py::init<const opencascade::handle<StepShape_FaceSurface> &, StepToTopoDS_Tool &, StepToTopoDS_NMTool &>(), py::arg("FS"), py::arg("T"), py::arg("NMTool"));

// Fields

// Methods
// cls_StepToTopoDS_TranslateFace.def_static("operator new_", (void * (*)(size_t)) &StepToTopoDS_TranslateFace::operator new, "None", py::arg("theSize"));
// cls_StepToTopoDS_TranslateFace.def_static("operator delete_", (void (*)(void *)) &StepToTopoDS_TranslateFace::operator delete, "None", py::arg("theAddress"));
// cls_StepToTopoDS_TranslateFace.def_static("operator new[]_", (void * (*)(size_t)) &StepToTopoDS_TranslateFace::operator new[], "None", py::arg("theSize"));
// cls_StepToTopoDS_TranslateFace.def_static("operator delete[]_", (void (*)(void *)) &StepToTopoDS_TranslateFace::operator delete[], "None", py::arg("theAddress"));
// cls_StepToTopoDS_TranslateFace.def_static("operator new_", (void * (*)(size_t, void *)) &StepToTopoDS_TranslateFace::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_StepToTopoDS_TranslateFace.def_static("operator delete_", (void (*)(void *, void *)) &StepToTopoDS_TranslateFace::operator delete, "None", py::arg(""), py::arg(""));
cls_StepToTopoDS_TranslateFace.def("Init", (void (StepToTopoDS_TranslateFace::*)(const opencascade::handle<StepShape_FaceSurface> &, StepToTopoDS_Tool &, StepToTopoDS_NMTool &)) &StepToTopoDS_TranslateFace::Init, "None", py::arg("FS"), py::arg("T"), py::arg("NMTool"));
cls_StepToTopoDS_TranslateFace.def("Value", (const TopoDS_Shape & (StepToTopoDS_TranslateFace::*)() const) &StepToTopoDS_TranslateFace::Value, "None");
cls_StepToTopoDS_TranslateFace.def("Error", (StepToTopoDS_TranslateFaceError (StepToTopoDS_TranslateFace::*)() const) &StepToTopoDS_TranslateFace::Error, "None");

// Enums

}