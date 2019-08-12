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
#include <StepGeom_BezierCurve.hxx>
#include <StepData_StepWriter.hxx>
#include <Interface_EntityIterator.hxx>
#include <RWStepGeom_RWBezierCurve.hxx>

void bind_RWStepGeom_RWBezierCurve(py::module &mod){

py::class_<RWStepGeom_RWBezierCurve, std::unique_ptr<RWStepGeom_RWBezierCurve, Deleter<RWStepGeom_RWBezierCurve>>> cls_RWStepGeom_RWBezierCurve(mod, "RWStepGeom_RWBezierCurve", "Read & Write Module for BezierCurve");

// Constructors
cls_RWStepGeom_RWBezierCurve.def(py::init<>());

// Fields

// Methods
// cls_RWStepGeom_RWBezierCurve.def_static("operator new_", (void * (*)(size_t)) &RWStepGeom_RWBezierCurve::operator new, "None", py::arg("theSize"));
// cls_RWStepGeom_RWBezierCurve.def_static("operator delete_", (void (*)(void *)) &RWStepGeom_RWBezierCurve::operator delete, "None", py::arg("theAddress"));
// cls_RWStepGeom_RWBezierCurve.def_static("operator new[]_", (void * (*)(size_t)) &RWStepGeom_RWBezierCurve::operator new[], "None", py::arg("theSize"));
// cls_RWStepGeom_RWBezierCurve.def_static("operator delete[]_", (void (*)(void *)) &RWStepGeom_RWBezierCurve::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepGeom_RWBezierCurve.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepGeom_RWBezierCurve::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepGeom_RWBezierCurve.def_static("operator delete_", (void (*)(void *, void *)) &RWStepGeom_RWBezierCurve::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepGeom_RWBezierCurve.def("ReadStep", (void (RWStepGeom_RWBezierCurve::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepGeom_BezierCurve> &) const) &RWStepGeom_RWBezierCurve::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepGeom_RWBezierCurve.def("WriteStep", (void (RWStepGeom_RWBezierCurve::*)(StepData_StepWriter &, const opencascade::handle<StepGeom_BezierCurve> &) const) &RWStepGeom_RWBezierCurve::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepGeom_RWBezierCurve.def("Share", (void (RWStepGeom_RWBezierCurve::*)(const opencascade::handle<StepGeom_BezierCurve> &, Interface_EntityIterator &) const) &RWStepGeom_RWBezierCurve::Share, "None", py::arg("ent"), py::arg("iter"));

// Enums

}