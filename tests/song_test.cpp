#include "song.h"
#include <lastfm/Track>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "test_utils.h"
#include "mock_taglib.h"

namespace {

class SongTest : public ::testing::Test {
 protected:
  static void SetUpTestCase() {
    // Return something from uninteresting mock functions.
    testing::DefaultValue<TagLib::String>::Set("foobarbaz");
  }

  MockFileRefFactory mock_factory_;
};


TEST_F(SongTest, InitsFromLastFM) {
  Song song;
  lastfm::MutableTrack track;
  track.setTitle("Foo");
  lastfm::Artist artist("Bar");
  track.setArtist(artist);
  lastfm::Album album(artist, "Baz");
  track.setAlbum(album);

  song.InitFromLastFM(track);
  EXPECT_EQ("Foo", song.title());
  EXPECT_EQ("Baz", song.album());
  EXPECT_EQ("Bar", song.artist());
}

TEST_F(SongTest, InitsFromFile) {
  mock_factory_.ExpectCall("foobar.mp3", "Foo", "Bar", "Baz");
  Song song(&mock_factory_);
  song.InitFromFile("foobar.mp3", 42);
  EXPECT_EQ("Foo", song.title());
  EXPECT_EQ("Bar", song.artist());
  EXPECT_EQ("Baz", song.album());
}

}  // namespace
