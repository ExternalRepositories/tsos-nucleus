
/* By Tsuki Superior
 * Generic Filesystem File Quark
 *
 * This is the file type that the nucleus uses internally
 * to represent files
 * 
 */

#ifndef __TSOS_NUCLEUS_FILESYSTEM_FILE__
#define __TSOS_NUCLEUS_FILESYSTEM_FILE__

#include <generic/quark.hpp>
#include <generic/types.hpp>
#include <generic/filesystem_permissions.hpp>
#include <generic/array.hpp>
#include <generic/string.hpp>

class File
{
public:
  //Constructor of a file
  File(void);

  // Copy Constructor
  File(const File &file);

  //Constructor
  File(String &pa, Permissions &per);

  //Destructor
  ~File();

  //The path of the file
  String path;

  //The permissions the file was opened in
  Permissions permissions;
};

#endif
