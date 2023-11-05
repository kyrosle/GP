set(third_party_folder "ThirdParty")
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

if (NOT TARGET glm)
  add_subdirectory(glm)
  set_target_properties(
      glm PROPERTIES FOLDER {third_party_folder}/glm)
endif ()

if (NOT TARGET stb)
  include(stb.cmake)
  set_target_properties(
      stb PROPERTIES FOLDER {third_party_folder}/stb)
endif ()

if (NOT TARGET imgui)
  include(imgui.cmake)
  set_target_properties(
      imgui PROPERTIES FOLDER {third_party_folder}/imgui)
endif ()

if (NOT TARGET spdlog)
  add_subdirectory(spdlog)
  set_target_properties(
      spdlog PROPERTIES FOLDER {third_party_folder}/spdlog)
endif ()

if (NOT TARGET json11)
  add_subdirectory(json11)
  set_target_properties(
      json11 PROPERTIES FOLDER {third_party_folder}/json11)
endif ()