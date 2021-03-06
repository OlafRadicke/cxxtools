/*
 * Copyright (C) 2013 Tommi Maekitalo
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * As a special exception, you may use this file as part of a free
 * software library without restriction. Specifically, if other files
 * instantiate templates or use macros or inline functions from this
 * file, or you compile this file and link it with other files to
 * produce an executable, this file does not by itself cause the
 * resulting executable to be covered by the GNU General Public
 * License. This exception does not however invalidate any other
 * reasons why the executable file might be covered by the GNU Library
 * General Public License.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "dateutils.h"
#include <stdexcept>
#include <cctype>

namespace cxxtools
{
  unsigned getUnsigned(std::string::const_iterator& b, std::string::const_iterator e, unsigned digits)
  {
    if (b == e || !std::isdigit(*b))
      throw std::runtime_error("invalid date format");

    unsigned ret = 0;
    for (unsigned d = 0; d < digits && b < e && std::isdigit(*b); ++d, ++b)
      ret = ret * 10 + (*b - '0');

    return ret;
  }

  unsigned getInt(std::string::const_iterator& b, std::string::const_iterator e, unsigned digits)
  {
    int sgn = 1;

    if (b != e)
    {
      if (*b == '-')
      {
        sgn = -1;
        ++b;
      }
      else if (*b == '+')
        ++b;
    }

    if (b == e || !std::isdigit(*b))
      throw std::runtime_error("invalid date format");

    int ret = 0;
    for (unsigned d = 0; d < digits && b < e && std::isdigit(*b); ++d, ++b)
      ret = ret * 10 + (*b - '0');

    return ret * sgn;
  }

  unsigned getMilliseconds(std::string::const_iterator& b, std::string::const_iterator e)
  {
    unsigned m = 0;

    if (!std::isdigit(*b))  // nothing
      return 0;

    m = (*b++ - '0') * 100;
    if (!std::isdigit(*b))  // .4  => 400 msec
      return m;

    m += (*b++ - '0') * 10;
    if (!std::isdigit(*b))  // .43  => 430 msec
      return m;

    m += (*b++ - '0');       // .432 => 432 msec
    return m;
  }

  void appendD4(std::string& s, unsigned v)
  {
      char d[4];
      d[3] = '0' + v % 10;
      v /= 10;
      d[2] = '0' + v % 10;
      v /= 10;
      d[1] = '0' + v % 10;
      v /= 10;
      d[0] = '0' + v % 10;
      s.append(d, 4);
  }

  void appendD3(std::string& s, unsigned v)
  {
      char d[3];
      d[2] = '0' + v % 10;
      v /= 10;
      d[1] = '0' + v % 10;
      v /= 10;
      d[0] = '0' + v % 10;
      s.append(d, 3);
  }

  void appendD2(std::string& s, unsigned v)
  {
      char d[2];
      d[1] = '0' + v % 10;
      v /= 10;
      d[0] = '0' + v % 10;
      s.append(d, 2);
  }

  void appendD1(std::string& s, unsigned short v)
  {
      s += '0' + v % 10;
  }

}
