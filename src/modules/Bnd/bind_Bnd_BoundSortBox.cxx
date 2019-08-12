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
#include <Bnd_Box.hxx>
#include <Standard_Handle.hxx>
#include <Bnd_HArray1OfBox.hxx>
#include <Standard_TypeDef.hxx>
#include <TColStd_ListOfInteger.hxx>
#include <gp_Pln.hxx>
#include <TColStd_DataMapOfIntegerInteger.hxx>
#include <Bnd_BoundSortBox.hxx>

void bind_Bnd_BoundSortBox(py::module &mod){

py::class_<Bnd_BoundSortBox, std::unique_ptr<Bnd_BoundSortBox, Deleter<Bnd_BoundSortBox>>> cls_Bnd_BoundSortBox(mod, "Bnd_BoundSortBox", "A tool to compare a bounding box or a plane with a set of bounding boxes. It sorts the set of bounding boxes to give the list of boxes which intersect the element being compared. The boxes being sorted generally bound a set of shapes, while the box being compared bounds a shape to be compared. The resulting list of intersecting boxes therefore gives the list of items which potentially intersect the shape to be compared.");

// Constructors
cls_Bnd_BoundSortBox.def(py::init<>());

// Fields

// Methods
// cls_Bnd_BoundSortBox.def_static("operator new_", (void * (*)(size_t)) &Bnd_BoundSortBox::operator new, "None", py::arg("theSize"));
// cls_Bnd_BoundSortBox.def_static("operator delete_", (void (*)(void *)) &Bnd_BoundSortBox::operator delete, "None", py::arg("theAddress"));
// cls_Bnd_BoundSortBox.def_static("operator new[]_", (void * (*)(size_t)) &Bnd_BoundSortBox::operator new[], "None", py::arg("theSize"));
// cls_Bnd_BoundSortBox.def_static("operator delete[]_", (void (*)(void *)) &Bnd_BoundSortBox::operator delete[], "None", py::arg("theAddress"));
// cls_Bnd_BoundSortBox.def_static("operator new_", (void * (*)(size_t, void *)) &Bnd_BoundSortBox::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_Bnd_BoundSortBox.def_static("operator delete_", (void (*)(void *, void *)) &Bnd_BoundSortBox::operator delete, "None", py::arg(""), py::arg(""));
cls_Bnd_BoundSortBox.def("Initialize", (void (Bnd_BoundSortBox::*)(const Bnd_Box &, const opencascade::handle<Bnd_HArray1OfBox> &)) &Bnd_BoundSortBox::Initialize, "Initializes this comparison algorithm with - the set of bounding boxes SetOfBox.", py::arg("CompleteBox"), py::arg("SetOfBox"));
cls_Bnd_BoundSortBox.def("Initialize", (void (Bnd_BoundSortBox::*)(const opencascade::handle<Bnd_HArray1OfBox> &)) &Bnd_BoundSortBox::Initialize, "Initializes this comparison algorithm with - the set of bounding boxes SetOfBox, where CompleteBox is given as the global bounding box of SetOfBox.", py::arg("SetOfBox"));
cls_Bnd_BoundSortBox.def("Initialize", (void (Bnd_BoundSortBox::*)(const Bnd_Box &, const Standard_Integer)) &Bnd_BoundSortBox::Initialize, "Initializes this comparison algorithm, giving it only - the maximum number nbComponents of the bounding boxes to be managed. Use the Add function to define the array of bounding boxes to be sorted by this algorithm.", py::arg("CompleteBox"), py::arg("nbComponents"));
cls_Bnd_BoundSortBox.def("Add", (void (Bnd_BoundSortBox::*)(const Bnd_Box &, const Standard_Integer)) &Bnd_BoundSortBox::Add, "Adds the bounding box theBox at position boxIndex in the array of boxes to be sorted by this comparison algorithm. This function is used only in conjunction with the third syntax described in the synopsis of Initialize.", py::arg("theBox"), py::arg("boxIndex"));
cls_Bnd_BoundSortBox.def("Compare", (const TColStd_ListOfInteger & (Bnd_BoundSortBox::*)(const Bnd_Box &)) &Bnd_BoundSortBox::Compare, "Compares the bounding box theBox, with the set of bounding boxes to be sorted by this comparison algorithm, and returns the list of intersecting bounding boxes as a list of indexes on the array of bounding boxes used by this algorithm.", py::arg("theBox"));
cls_Bnd_BoundSortBox.def("Compare", (const TColStd_ListOfInteger & (Bnd_BoundSortBox::*)(const gp_Pln &)) &Bnd_BoundSortBox::Compare, "Compares the plane P with the set of bounding boxes to be sorted by this comparison algorithm, and returns the list of intersecting bounding boxes as a list of indexes on the array of bounding boxes used by this algorithm.", py::arg("P"));
cls_Bnd_BoundSortBox.def("Dump", (void (Bnd_BoundSortBox::*)() const) &Bnd_BoundSortBox::Dump, "None");
cls_Bnd_BoundSortBox.def("Destroy", (void (Bnd_BoundSortBox::*)()) &Bnd_BoundSortBox::Destroy, "None");

// Enums

}