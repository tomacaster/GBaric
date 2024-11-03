#pragma once

namespace Players {
    enum class MediaType : int {
        Video = 0,
        Image = 1,
        Unknown = 2,
        Empty = 3
    };

    enum class MediaState : int {
        Stopped = 0,
        Playing = 1,
        Paused = 2,
        Seek = 3,
        Rewind = 4,
        Unknown = 5
    };

    enum class MediaEvent : int {
        Loading = 0,
        Loaded = 1,
        Releasing = 2,
        Released = 3
    };

    struct MediaContext;
}
