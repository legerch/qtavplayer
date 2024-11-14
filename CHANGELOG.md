# Changelog

All notable changes to this project will be documented in this file.  
The format is based on [Keep a Changelog] and this project adheres to [Semantic Versioning].

## [next] - 1.0.0
Creation of the fork library which differ from original by:
- Separating public and private headers
- Use lowercase "qtavplayer" in path to ease includes (and linking)
- Remove usage of _Qt private header_ (directly include them)
- Provide a CMake file which ease integration in other projects
- Provide a semanctic versionning (which is currently set to `0.0.1`)
- Use proper Qt logger level (instead of using `qDebug()` everywhere)
- Allow to set _FFmpeg_ log level

<!-- Links -->
[keep a changelog]: https://keepachangelog.com/en/1.0.0/
[semantic versioning]: https://semver.org/spec/v2.0.0.html

<!-- Versions -->
[next]: https://github.com/Author/Repository/compare/v0.0.2...HEAD
[0.0.2]: https://github.com/Author/Repository/compare/v0.0.1...v0.0.2
[0.0.1]: https://github.com/Author/Repository/releases/tag/v0.0.1