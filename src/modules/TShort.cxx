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
#include <NCollection_Array1.hxx>
#include <Standard_TypeDef.hxx>
#include <TShort_Array1OfShortReal.hxx>
#include <Standard_Transient.hxx>
#include <Standard.hxx>
#include <Standard_Handle.hxx>
#include <NCollection_BaseAllocator.hxx>
#include <Standard_Std.hxx>
#include <TShort_HArray1OfShortReal.hxx>
#include <Standard_Type.hxx>
#include <NCollection_Array2.hxx>
#include <TShort_Array2OfShortReal.hxx>
#include <TShort_HArray2OfShortReal.hxx>
#include <NCollection_Sequence.hxx>
#include <TShort_SequenceOfShortReal.hxx>
#include <TShort_HSequenceOfShortReal.hxx>
#include <bind_NCollection_Array1.hxx>
#include <bind_Define_HArray1.hxx>
#include <bind_NCollection_Array2.hxx>
#include <bind_Define_HArray2.hxx>
#include <bind_NCollection_Sequence.hxx>
#include <bind_Define_HSequence.hxx>

PYBIND11_MODULE(TShort, mod) {

py::module::import("OCCT.NCollection");
py::module::import("OCCT.Standard");

// TYPEDEF: TSHORT_ARRAY1OFSHORTREAL
bind_NCollection_Array1<float>(mod, "TShort_Array1OfShortReal", py::module_local(false));

// CLASS: TSHORT_HARRAY1OFSHORTREAL
bind_Define_HArray1<TShort_HArray1OfShortReal, TShort_Array1OfShortReal>(mod, "TShort_HArray1OfShortReal");

// TYPEDEF: TSHORT_ARRAY2OFSHORTREAL
bind_NCollection_Array2<float>(mod, "TShort_Array2OfShortReal", py::module_local(false));

// CLASS: TSHORT_HARRAY2OFSHORTREAL
bind_Define_HArray2<TShort_HArray2OfShortReal, TShort_Array2OfShortReal>(mod, "TShort_HArray2OfShortReal");

// TYPEDEF: TSHORT_SEQUENCEOFSHORTREAL
bind_NCollection_Sequence<float>(mod, "TShort_SequenceOfShortReal", py::module_local(false));

// CLASS: TSHORT_HSEQUENCEOFSHORTREAL
bind_Define_HSequence<TShort_HSequenceOfShortReal, TShort_SequenceOfShortReal>(mod, "TShort_HSequenceOfShortReal");


}
