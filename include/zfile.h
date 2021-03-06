/*  =========================================================================
    zfile - helper functions for working with files.

    Copyright (c) the Contributors as noted in the AUTHORS file.
    This file is part of CZMQ, the high-level C binding for 0MQ:
    http://czmq.zeromq.org.

    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.
    =========================================================================
*/

#ifndef __ZFILE_H_INCLUDED__
#define __ZFILE_H_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

//  @interface
//  If file exists, populates properties. CZMQ supports portable symbolic
//  links, which are files with the extension ".ln". A symbolic link is a
//  text file containing one line, the filename of a target file. Reading
//  data from the symbolic link actually reads from the target file. Path
//  may be NULL, in which case it is not used.
CZMQ_EXPORT zfile_t *
    zfile_new (const char *path, const char *name);

//  Destroy a file item
CZMQ_EXPORT void
    zfile_destroy (zfile_t **self_p);

//  Duplicate a file item, returns a newly constructed item. If the file
//  is null, or memory was exhausted, returns null.
CZMQ_EXPORT zfile_t *
    zfile_dup (zfile_t *self);

//  Return file name, remove path if provided
CZMQ_EXPORT char *
    zfile_filename (zfile_t *self, const char *path);

//  Refresh file properties from disk; this is not done automatically
//  on access methods, otherwise it is not possible to compare directory
//  snapshots.
CZMQ_EXPORT void
    zfile_restat (zfile_t *self);

//  Return when the file was last modified. If you want this to reflect the
//  current situation, call zfile_restat before checking this property.
CZMQ_EXPORT time_t
    zfile_modified (zfile_t *self);

//  Return the last-known size of the file. If you want this to reflect the
//  current situation, call zfile_restat before checking this property.
CZMQ_EXPORT off_t
    zfile_cursize (zfile_t *self);

//  Return true if the file is a directory. If you want this to reflect
//  any external changes, call zfile_restat before checking this property.
CZMQ_EXPORT bool
    zfile_is_directory (zfile_t *self);

//  Return true if the file is a regular file. If you want this to reflect
//  any external changes, call zfile_restat before checking this property.
CZMQ_EXPORT bool
    zfile_is_regular (zfile_t *self);

//  Return true if the file is readable by this process. If you want this to
//  reflect any external changes, call zfile_restat before checking this
//  property.
CZMQ_EXPORT bool
    zfile_is_readable (zfile_t *self);

//  Return true if the file is writeable by this process. If you want this
//  to reflect any external changes, call zfile_restat before checking this
//  property.
CZMQ_EXPORT bool
    zfile_is_writeable (zfile_t *self);

//  Check if file has stopped changing and can be safely processed.
//  Updates the file statistics from disk at every call.
CZMQ_EXPORT bool
    zfile_is_stable (zfile_t *self);

//  Return true if the file was changed on disk since the zfile_t object
//  was created, or the last zfile_restat() call made on it.
CZMQ_EXPORT bool
    zfile_has_changed (zfile_t *self);

//  Remove the file from disk
CZMQ_EXPORT void
    zfile_remove (zfile_t *self);

//  Open file for reading
//  Returns 0 if OK, -1 if not found or not accessible
CZMQ_EXPORT int
    zfile_input (zfile_t *self);

//  Open file for writing, creating directory if needed
//  File is created if necessary; chunks can be written to file at any
//  location. Returns 0 if OK, -1 if error.
CZMQ_EXPORT int
    zfile_output (zfile_t *self);

//  Read chunk from file at specified position. If this was the last chunk,
//  sets the eof property. Returns a null chunk in case of error.
CZMQ_EXPORT zchunk_t *
    zfile_read (zfile_t *self, size_t bytes, off_t offset);

//  Returns true if zfile_read() just read the last chunk in the file.
CZMQ_EXPORT bool
    zfile_eof (zfile_t *self);
    
//  Write chunk to file at specified position
//  Return 0 if OK, else -1
CZMQ_EXPORT int
    zfile_write (zfile_t *self, zchunk_t *chunk, off_t offset);

//  Read next line of text from file. Returns a pointer to the text line,
//  or NULL if there was nothing more to read from the file.
CZMQ_EXPORT const char *
    zfile_readln (zfile_t *self);
    
//  Close file, if open
CZMQ_EXPORT void
    zfile_close (zfile_t *self);

//  Return file handle, if opened
CZMQ_EXPORT FILE *
    zfile_handle (zfile_t *self);

//  Calculate SHA1 digest for file, using zdigest class.
CZMQ_EXPORT const char *
    zfile_digest (zfile_t *self);

//  Self test of this class
CZMQ_EXPORT void
    zfile_test (bool verbose);
//  @end

//  @interface
//  These methods are deprecated, and now moved to zsys class.
CZMQ_EXPORT bool
    zfile_exists (const char *filename);
CZMQ_EXPORT ssize_t
    zfile_size   (const char *filename);
CZMQ_EXPORT mode_t
    zfile_mode   (const char *filename);
CZMQ_EXPORT int
    zfile_delete (const char *filename);
CZMQ_EXPORT bool
    zfile_stable (const char *filename);
CZMQ_EXPORT int
    zfile_mkdir  (const char *pathname);
CZMQ_EXPORT int
    zfile_rmdir  (const char *pathname);
CZMQ_EXPORT void
    zfile_mode_private (void);
CZMQ_EXPORT void
    zfile_mode_default (void);
//  @end

#ifdef __cplusplus
}
#endif


#endif  //  __ZFILE_H_INCLUDED__
