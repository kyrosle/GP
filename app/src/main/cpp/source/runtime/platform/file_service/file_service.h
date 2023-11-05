#pragma once

#include <vector>
#include <memory>
#include <android/asset_manager.h>

namespace Gp {
  /*!
   * Android file system wrapped,
   * depending `AAssetManager`(android/asset_manager.h)
   *
   * all method should use after calling @a initialize(struct AAssetManager*)
   */
  class FileSystem {
  public:
    typedef std::shared_ptr<FileSystem> ptr;
    typedef AAsset File;
    typedef AAssetDir Dir;

    FileSystem() = default;

    ~FileSystem() = default;

    /*! Available access modes for opening assets with
     * {@link FileSystem::open}
     */
    enum class FileMode : int {
      /** No specific information about how data will be accessed. **/
      UNKNOWN = 0,
      /** Read chunks, and seek forward and backward. */
      RANDOM = 1,
      /** Read sequentially, with an occasional forward seek. */
      STREAMING = 2,
      /** Caller plans to ask for a read-only buffer with all data. */
      BUFFER = 3
    };

    /*!
     * initialize the file system, binding the AAssetManager
     */
    void initialize(struct AAssetManager *manager);

    // expose the asset_manager interface:

    /*!
     * Open the named directory within the asset hierarchy.
     * The directory  can then be inspected with the AAssetDir functions.
     * To open the top-level directory, pass in "" as the dirName.
     *
     * The object returned here should be freed by calling AAssetDir_close().
     */
    Dir *openDir(const char *dirName) {
      return AAssetManager_openDir(m_manger, dirName);
    }

    /*!
     * Open an asset.
     *
     * The object returned here should be freed by calling AAsset_close().
     */
    File *open(const char *filename, FileMode mode) {
      return AAssetManager_open(m_manger, filename, (int) mode);
    }

    /*!
     *  Iterate over the files in an asset directory.
     *  A NULL string is returned when all the file names
     *  have been returned.
     *
     *  The returned file name is suitable for passing to AAssetManager_open().
     *
     *  The string returned here is owned by the AssetDir implementation and
     *  is not guaranteed to remain valid if any other calls are made on this
     *  AAssetDir instance.
     */
    static const char *getNextFileName(Dir *assetDir) {
      return AAssetDir_getNextFileName(assetDir);
    }

    /*!
     * Reset the iteration state of AAssetDir_getNextFileName()
     * to the beginning.
     */
    static void rewind(Dir *assetDir) {
      return AAssetDir_rewind(assetDir);
    }

    /*!
     * CLose an opened AAssetDir, freeing any relate resources.
     */
    static void dir_close(Dir *assetDir) {
      return AAssetDir_close(assetDir);
    }

    /*!
     * Attempt to read `count` bytes of data from the current offset.
     *
     * Returns the number of bytes read, zero on EOF, or < 0 on error.
     */
    static int read(File *asset, void *buf, size_t count) {
      return AAsset_read(asset, buf, count);
    }

    /*!
     * Seek to the specified offset within the asset data.
     * `whence` uses the same constants as lseek()/fseek().
     *
     * Returns the new position on success, or (off_t) -1 on error.
     */
    static off_t seek(File *asset, off_t offset, int whence) {
      return AAsset_seek(asset, offset, whence);
    }

    /*!
     * Seek to the specified offset within the asset data.
     * `whence` uses the same constants as lseek()/fseek().
     *
     * Uses 64-bit data type for large files as opposed to
     * 32-bit type used by AAsset_seek.
     *
     * Returns the new position on success, or (off64_t) -1 on error.
     */
    static off64_t seek64(File *asset, off64_t offset, int whence) {
      return AAsset_seek64(asset, offset, whence);
    }

    /*!
     * Close the asset, freeing all associated resources.
     */
    static void file_close(File *asset) {
      return AAsset_close(asset);
    }

    /*!
     * Get a pointer to a buffer holding the entire contents
     * of the asset.
     *
     * Returns NULL on failure.
     */
    static const void *getBuffer(File *asset) {
      return AAsset_getBuffer(asset);
    }

    /*!
     * Report the total size of the asset data.
     */
    static off_t getLength(File *asset) {
      return AAsset_getLength(asset);
    }

    /*!
     * Report the total size of the asset data.
     *
     * Reports the size using a 64-bit number instead of 32-bit as
     * AAsset_getLength.
     */
    static off64_t getLength64(File *asset) {
      return AAsset_getLength(asset);
    }

    /*!
     * Reports the total amount of asset data that can be read from the
     * current position.
     */
    static off_t getRemainingLength(File *asset) {
      return AAsset_getRemainingLength(asset);
    }

    /*!
     * Reports the total amount of asset data that can be read from the
     * current position.
     *
     * Uses a 64-bit number instead of 32-bit as AAsset_getRemainingLength.
     */
    static off64_t getRemainingLength64(File *asset) {
      return AAsset_getRemainingLength(asset);
    }

    /*!
     * Open a new file descriptor that can be used to read the asset data.
     * If the start or length cannot be represented by a 32-by number,
     * it will be truncated.
     * If the file is large, use AAsset_openFileDescriptor64 instead.
     *
     * Return < 0 if direct fd access is not possible
     * (for example, if the asset is compressed).
     */
    static int
    openFileDescriptor(File *asset, off_t *outStart, off_t *outLength) {
      return AAsset_openFileDescriptor(asset, outStart, outLength);
    }

    /**
     * Open a new file descriptor that can be used to read the asset data.
     *
     * Uses a 64-bit number for the offset and length instead of 32-bit instead of
     * as AAsset_openFileDescriptor does.
     *
     * Returns < 0 if direct fd access is not possible (for example, if the asset is
     * compressed).
     */
    static int openFileDescriptor64(AAsset *asset, off64_t *outStart,
                                    off64_t *outLength) {
      return AAsset_openFileDescriptor64(asset, outStart, outLength);
    }

    /*!
     * Returns whether this asset's internal buffer is allocated in ordinary RAM
     * (i.e. not mmapped)
     */
    static int isAllocated(File *asset) {
      return AAsset_isAllocated(asset);
    }

  private:
    struct AAssetManager *m_manger;
  };
}
