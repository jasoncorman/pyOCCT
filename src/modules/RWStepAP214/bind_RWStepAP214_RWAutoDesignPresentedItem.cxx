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
#include <StepAP214_AutoDesignPresentedItem.hxx>
#include <StepData_StepWriter.hxx>
#include <Interface_EntityIterator.hxx>
#include <RWStepAP214_RWAutoDesignPresentedItem.hxx>

void bind_RWStepAP214_RWAutoDesignPresentedItem(py::module &mod){

py::class_<RWStepAP214_RWAutoDesignPresentedItem, std::unique_ptr<RWStepAP214_RWAutoDesignPresentedItem, Deleter<RWStepAP214_RWAutoDesignPresentedItem>>> cls_RWStepAP214_RWAutoDesignPresentedItem(mod, "RWStepAP214_RWAutoDesignPresentedItem", "Read & Write Module for AutoDesignPresentedItem");

// Constructors
cls_RWStepAP214_RWAutoDesignPresentedItem.def(py::init<>());

// Fields

// Methods
// cls_RWStepAP214_RWAutoDesignPresentedItem.def_static("operator new_", (void * (*)(size_t)) &RWStepAP214_RWAutoDesignPresentedItem::operator new, "None", py::arg("theSize"));
// cls_RWStepAP214_RWAutoDesignPresentedItem.def_static("operator delete_", (void (*)(void *)) &RWStepAP214_RWAutoDesignPresentedItem::operator delete, "None", py::arg("theAddress"));
// cls_RWStepAP214_RWAutoDesignPresentedItem.def_static("operator new[]_", (void * (*)(size_t)) &RWStepAP214_RWAutoDesignPresentedItem::operator new[], "None", py::arg("theSize"));
// cls_RWStepAP214_RWAutoDesignPresentedItem.def_static("operator delete[]_", (void (*)(void *)) &RWStepAP214_RWAutoDesignPresentedItem::operator delete[], "None", py::arg("theAddress"));
// cls_RWStepAP214_RWAutoDesignPresentedItem.def_static("operator new_", (void * (*)(size_t, void *)) &RWStepAP214_RWAutoDesignPresentedItem::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_RWStepAP214_RWAutoDesignPresentedItem.def_static("operator delete_", (void (*)(void *, void *)) &RWStepAP214_RWAutoDesignPresentedItem::operator delete, "None", py::arg(""), py::arg(""));
cls_RWStepAP214_RWAutoDesignPresentedItem.def("ReadStep", (void (RWStepAP214_RWAutoDesignPresentedItem::*)(const opencascade::handle<StepData_StepReaderData> &, const Standard_Integer, opencascade::handle<Interface_Check> &, const opencascade::handle<StepAP214_AutoDesignPresentedItem> &) const) &RWStepAP214_RWAutoDesignPresentedItem::ReadStep, "None", py::arg("data"), py::arg("num"), py::arg("ach"), py::arg("ent"));
cls_RWStepAP214_RWAutoDesignPresentedItem.def("WriteStep", (void (RWStepAP214_RWAutoDesignPresentedItem::*)(StepData_StepWriter &, const opencascade::handle<StepAP214_AutoDesignPresentedItem> &) const) &RWStepAP214_RWAutoDesignPresentedItem::WriteStep, "None", py::arg("SW"), py::arg("ent"));
cls_RWStepAP214_RWAutoDesignPresentedItem.def("Share", (void (RWStepAP214_RWAutoDesignPresentedItem::*)(const opencascade::handle<StepAP214_AutoDesignPresentedItem> &, Interface_EntityIterator &) const) &RWStepAP214_RWAutoDesignPresentedItem::Share, "None", py::arg("ent"), py::arg("iter"));

// Enums

}