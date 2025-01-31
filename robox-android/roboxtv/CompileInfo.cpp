/*
 *      Copyright (C) 2014 Team XBMC
 *      http://xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "CompileInfo.h"
#include <cstddef>

#if defined(TARGET_WINDOWS) && !defined(_DEBUG)
#include "../git_revision.h" // generated file
#endif


int CCompileInfo::GetMajor()
{
  return 1;
}

int CCompileInfo::GetMinor()
{
  return 0;
}

const char* CCompileInfo::GetAppName()
{
  return "RoBoXTV";
}

const char* CCompileInfo::GetSuffix()
{
  return "beta1";
}

const char* CCompileInfo::GetSCMID()
{
#if defined(TARGET_WINDOWS)
#ifdef GIT_REV
  return GIT_REV;
#else
  return "Unknown";
#endif
#endif
  return "2016-01-14-cd9b226-dirty";
}
