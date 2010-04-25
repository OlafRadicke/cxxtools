/*
 * Copyright (C) 2010 Tommi Maekitalo
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * is provided AS IS, WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, and
 * NON-INFRINGEMENT.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 *
 */

#include <iostream>
#include <cxxtools/mutex.h>
#include <cxxtools/threadpool.h>
#include <cxxtools/arg.h>

cxxtools::Mutex mutex;
unsigned count = 0;

void funct()
{
  for (unsigned n = 0; n < 10; ++n)
  {
    {
      cxxtools::MutexLock lock(mutex);
      std::cout << "Hello " << ++count << std::endl;
    }

    cxxtools::Thread::sleep(100);
  }
}

int main(int argc, char* argv[])
{
  try
  {
    cxxtools::Arg<unsigned> threads(argc, argv, 't', 5);
    cxxtools::Arg<unsigned> tasks(argc, argv, 'n', 20);
    cxxtools::Arg<bool> docancel(argc, argv, 'c');

    cxxtools::ThreadPool p(threads);

    for (unsigned n = 0; n < tasks; ++n)
        p.schedule(cxxtools::callable(funct));

    if (docancel)
      p.stop(docancel);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
}

