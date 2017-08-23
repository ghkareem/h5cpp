//
// (c) Copyright 2017 DESY,ESS
//
// This file is part of h5cpp.
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation; either version 2.1 of the License, or
// (at your option) any later version.
//
// This library is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty ofMERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the
// Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor
// Boston, MA  02110-1301 USA
// ===========================================================================
//
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Aug 23, 2017
//
#pragma once

extern "C" {
#include <hdf5.h>
}

namespace hdf5 {
namespace datatype {

template<typename T>
hid_t copy_native_type()
{
  return 0;
}

#define COPY_NATIVE_TYPE_SPECIALIZATION_DECL(type) \
  template<> hid_t copy_native_type<type>();

#define COPY_NATIVE_TYPE_SPECIALIZATION(type,native_id)\
  template<> \
  hid_t copy_native_type<type>() \
  { \
    return H5Tcopy(native_id); \
  }

COPY_NATIVE_TYPE_SPECIALIZATION_DECL(char)
COPY_NATIVE_TYPE_SPECIALIZATION_DECL(unsigned char)
COPY_NATIVE_TYPE_SPECIALIZATION_DECL(signed char)
COPY_NATIVE_TYPE_SPECIALIZATION_DECL(short)
COPY_NATIVE_TYPE_SPECIALIZATION_DECL(unsigned short)
COPY_NATIVE_TYPE_SPECIALIZATION_DECL(int)
COPY_NATIVE_TYPE_SPECIALIZATION_DECL(unsigned int)
COPY_NATIVE_TYPE_SPECIALIZATION_DECL(long)
COPY_NATIVE_TYPE_SPECIALIZATION_DECL(unsigned long)
COPY_NATIVE_TYPE_SPECIALIZATION_DECL(long long)
COPY_NATIVE_TYPE_SPECIALIZATION_DECL(unsigned long long)
COPY_NATIVE_TYPE_SPECIALIZATION_DECL(float)
COPY_NATIVE_TYPE_SPECIALIZATION_DECL(double)
COPY_NATIVE_TYPE_SPECIALIZATION_DECL(long double)



} // namespace datatype
} // namespace hdf5
