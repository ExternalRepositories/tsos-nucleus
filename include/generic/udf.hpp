/* By Tsuki Superior
 * Universal Disk Filesystem Quark
 * 
 * Normally filesystem quarks are multiplatform, but
 * this one is for PC only, because as of TS/OS version 0.0
 * the only drive that can be read from is the one that was booted from,
 * and this is most likely to happen on PC for UDF, because its used on Disks
 */

#ifndef __TSOS_UDF_QUARK__
#define __TSOS_UDF_QUARK__

#include <generic/filesystem_quark.hpp>
#include <generic/filesystem_file.hpp>
#include <generic/array.hpp>

class UDF_quark : public Filesystem_quark
{
public:
  UDF_quark(void);
  bool detectsystem(void) final;
  void reset(void) final;
  Array<String &> &readdir(String &path) final;
  void rename(String &path, char *newPath) final;
  File open(String &path) final;
  void close(File file) final;
  char *read(File file) final;
  void write(File file, char *data) final;
  char *readfile(String &path) final;
  void writefile(String &path, char *data) final;
  void appendfile(String &path, char *data) final;
  bool exists(String &path) final;
  bool isfilenamevalid(char *name) final;

private:
  char *currentdirectory;
  File openfiles[128];

  enum class volume_descriptor_type_code : uint8_t
  {
    BOOT_RECORD = 0,
    PRIMARY_VOLUME_DESCRIPTOR = 1,
    SUPPLEMENTARY_VOLUME_DESCRIPTOR = 2,
    VOLUME_PARTITION_DESCRIPTOR = 3,
    // Reserved 4-254
    VOLUME_DESCRIPTOR_SET_TERMINATOR = 255
  };

  class Primary_Volume_Descriptor
  {
  public:
    volume_descriptor_type_code type_code;

  } __attribute__((packed));

  class Boot_Record
  {
  public:
    volume_descriptor_type_code type_code;
    char type_identifier[5];
    uint8_t version;
    char boot_system_identifier[32];
    char boot_identifier[32];
  } __attribute__((packed));

  class Volume_Descriptor_Set_Terminator
  {
  public:
    uint8_t type_code;

  } __attribute__((packed));

  class Path_Table_Entry
  {
  public:
    uint8_t directory_identifier_length;
    uint8_t extended_attribute_record_length;
    uint64_t extent_location;
    uint16_t parent_directory_number;
    char *directory_identifier;
  } __attribute__((packed));
};

#endif