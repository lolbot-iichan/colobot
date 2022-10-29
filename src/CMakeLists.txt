# Compile flags as defined in global CMakeLists
set(CMAKE_CXX_FLAGS ${COLOBOT_CXX_FLAGS})
set(CMAKE_CXX_FLAGS_RELEASE ${COLOBOT_CXX_FLAGS_RELEASE})
set(CMAKE_CXX_FLAGS_DEBUG ${COLOBOT_CXX_FLAGS_DEBUG})

# Subdirectories
add_subdirectory(CBot)

if(TOOLS)
    #add_subdirectory(tools)
endif()

add_subdirectory(graphics/opengl33/shaders)

# Configure file
configure_file(common/config.h.cmake "${CMAKE_CURRENT_BINARY_DIR}/common/config.h")
configure_file(common/version.h.cmake "${CMAKE_CURRENT_BINARY_DIR}/common/version.h")

# Todo: split this monstrosity into smaller libraries (graphics, math, ui, etc.)
add_library(colobotbase STATIC
    app/app.cpp
    app/app.h
    app/controller.cpp
    app/controller.h
    app/input.cpp
    app/input.h
    app/modman.cpp
    app/modman.h
    app/pathman.cpp
    app/pathman.h
    app/pausemanager.cpp
    app/pausemanager.h
    app/signal_handlers.cpp
    app/signal_handlers.h
    common/config_file.cpp
    common/config_file.h
    common/error.h
    common/event.cpp
    common/event.h
    common/font_loader.h
    common/font_loader.cpp
    common/global.h
    common/image.cpp
    common/image.h
    common/ioutils.h
    common/key.cpp
    common/key.h
    common/language.cpp
    common/language.h
    common/logger.cpp
    common/logger.h
    common/profiler.cpp
    common/profiler.h
    common/regex_utils.cpp
    common/regex_utils.h
    common/resources/inputstream.cpp
    common/resources/inputstream.h
    common/resources/inputstreambuffer.cpp
    common/resources/inputstreambuffer.h
    common/resources/outputstream.cpp
    common/resources/outputstream.h
    common/resources/outputstreambuffer.cpp
    common/resources/outputstreambuffer.h
    common/resources/resourcemanager.cpp
    common/resources/resourcemanager.h
    common/resources/sdl_file_wrapper.cpp
    common/resources/sdl_file_wrapper.h
    common/resources/sdl_memory_wrapper.cpp
    common/resources/sdl_memory_wrapper.h
    common/resources/sndfile_wrapper.cpp
    common/resources/sndfile_wrapper.h
    common/restext.cpp
    common/restext.h
    common/system/system.cpp
    common/system/system.h
    common/system/system_other.cpp
    common/system/system_other.h
    common/system/${SYSTEM_CPP_MODULE}
    common/system/${SYSTEM_H_MODULE}
    common/settings.cpp
    common/settings.h
    common/singleton.h
    common/stringutils.cpp
    common/stringutils.h
    common/timeutils.cpp
    common/timeutils.h
    common/thread/worker_thread.h
    graphics/core/color.cpp
    graphics/core/color.h
    graphics/core/device.h
    graphics/core/framebuffer.cpp
    graphics/core/framebuffer.h
    graphics/core/light.h
    graphics/core/material.h
    graphics/core/texture.h
    graphics/core/transparency.h
    graphics/core/triangle.h
    graphics/core/type.cpp
    graphics/core/type.h
    graphics/core/renderers.h
    graphics/core/vertex.h
    graphics/engine/camera.cpp
    graphics/engine/camera.h
    graphics/engine/cloud.cpp
    graphics/engine/cloud.h
    graphics/engine/engine.cpp
    graphics/engine/engine.h
    graphics/engine/lightman.cpp
    graphics/engine/lightman.h
    graphics/engine/lightning.cpp
    graphics/engine/lightning.h
    graphics/engine/oldmodelmanager.cpp
    graphics/engine/oldmodelmanager.h
    graphics/engine/particle.cpp
    graphics/engine/particle.h
    graphics/engine/planet.cpp
    graphics/engine/planet.h
    graphics/engine/pyro.cpp
    graphics/engine/pyro.h
    graphics/engine/pyro_manager.cpp
    graphics/engine/pyro_manager.h
    graphics/engine/pyro_type.h
    graphics/engine/terrain.cpp
    graphics/engine/terrain.h
    graphics/engine/text.cpp
    graphics/engine/text.h
    graphics/engine/trace_color.cpp
    graphics/engine/trace_color.h
    graphics/engine/water.cpp
    graphics/engine/water.h
    graphics/model/model.cpp
    graphics/model/model.h
    graphics/model/model_crash_sphere.h
    graphics/model/model_input.cpp
    graphics/model/model_input.h
    graphics/model/model_io_exception.h
    graphics/model/model_io_structs.h
    graphics/model/model_gltf.cpp
    graphics/model/model_gltf.h
    graphics/model/model_manager.cpp
    graphics/model/model_manager.h
    graphics/model/model_mesh.cpp
    graphics/model/model_mesh.h
    graphics/model/model_mod.cpp
    graphics/model/model_mod.h
    graphics/model/model_output.cpp
    graphics/model/model_output.h
    graphics/model/model_shadow_spot.h
    graphics/model/model_triangle.h
    graphics/model/model_txt.cpp
    graphics/model/model_txt.h
    graphics/opengl33/gl33_device.cpp
    graphics/opengl33/gl33_device.h
    graphics/opengl33/gl33_object_renderer.cpp
    graphics/opengl33/gl33_object_renderer.h
    graphics/opengl33/gl33_particle_renderer.cpp
    graphics/opengl33/gl33_particle_renderer.h
    graphics/opengl33/gl33_terrain_renderer.cpp
    graphics/opengl33/gl33_terrain_renderer.h
    graphics/opengl33/gl33_shadow_renderer.cpp
    graphics/opengl33/gl33_shadow_renderer.h
    graphics/opengl33/gl33_ui_renderer.cpp
    graphics/opengl33/gl33_ui_renderer.h
    graphics/opengl33/glframebuffer.cpp
    graphics/opengl33/glframebuffer.h
    graphics/opengl33/glutil.cpp
    graphics/opengl33/glutil.h
    level/build_type.h
    level/drive_type.h
    level/level_category.cpp
    level/level_category.h
    level/mainmovie.cpp
    level/mainmovie.h
    level/mission_type.h
    level/parser/parser.cpp
    level/parser/parser.h
    level/parser/parserexceptions.cpp
    level/parser/parserexceptions.h
    level/parser/parserline.cpp
    level/parser/parserline.h
    level/parser/parserparam.cpp
    level/parser/parserparam.h
    level/player_profile.cpp
    level/player_profile.h
    level/research_type.h
    level/robotmain.cpp
    level/robotmain.h
    level/scene_conditions.cpp
    level/scene_conditions.h
    level/scoreboard.cpp
    level/scoreboard.h
    level/tool_type.h
    math/all.h
    math/const.h
    math/func.h
    math/geometry.h
    math/half.cpp
    math/half.h
    math/sphere.h
    object/auto/auto.cpp
    object/auto/auto.h
    object/auto/autobase.cpp
    object/auto/autobase.h
    object/auto/autoboat.cpp
    object/auto/autoboat.h
    object/auto/autoconvert.cpp
    object/auto/autoconvert.h
    object/auto/autoderrick.cpp
    object/auto/autoderrick.h
    object/auto/autodestroyer.cpp
    object/auto/autodestroyer.h
    object/auto/autoegg.cpp
    object/auto/autoegg.h
    object/auto/autofactory.cpp
    object/auto/autofactory.h
    object/auto/autofan.cpp
    object/auto/autofan.h
    object/auto/autoflag.cpp
    object/auto/autoflag.h
    object/auto/autohouston.cpp
    object/auto/autohouston.h
    object/auto/autoinfo.cpp
    object/auto/autoinfo.h
    object/auto/autojostle.cpp
    object/auto/autojostle.h
    object/auto/autolabo.cpp
    object/auto/autolabo.h
    object/auto/autolamp.cpp
    object/auto/autolamp.h
    object/auto/automush.cpp
    object/auto/automush.h
    object/auto/autonest.cpp
    object/auto/autonest.h
    object/auto/autonuclearplant.cpp
    object/auto/autonuclearplant.h
    object/auto/autoorgacannon.cpp
    object/auto/autoorgacannon.h
    object/auto/autoportico.cpp
    object/auto/autoportico.h
    object/auto/autopowercaptor.cpp
    object/auto/autopowercaptor.h
    object/auto/autopowerplant.cpp
    object/auto/autopowerplant.h
    object/auto/autopowerstation.cpp
    object/auto/autopowerstation.h
    object/auto/autoradar.cpp
    object/auto/autoradar.h
    object/auto/autorepair.cpp
    object/auto/autorepair.h
    object/auto/autoresearch.cpp
    object/auto/autoresearch.h
    object/auto/autoroot.cpp
    object/auto/autoroot.h
    object/auto/autotower.cpp
    object/auto/autotower.h
    object/auto/autotrunk.cpp
    object/auto/autotrunk.h
    object/auto/autovault.cpp
    object/auto/autovault.h
    object/auto/autoworm.cpp
    object/auto/autoworm.h
    object/auto/autoquarz.cpp
    object/auto/autoquarz.h
    object/crash_sphere.h
    object/details/assistant_details.cpp
    object/details/assistant_details.h
    object/details/automated_details.cpp
    object/details/automated_details.h
    object/details/controllable_details.cpp
    object/details/controllable_details.h
    object/details/damageable_details.cpp
    object/details/damageable_details.h
    object/details/destroyable_details.cpp
    object/details/destroyable_details.h
    object/details/details_provider.cpp
    object/details/details_provider.h
    object/details/detectable_details.cpp
    object/details/detectable_details.h
    object/details/exchange_post_details.cpp
    object/details/exchange_post_details.h
    object/details/flying_details.cpp
    object/details/flying_details.h
    object/details/fragile_details.cpp
    object/details/fragile_details.h
    object/details/global_details.cpp
    object/details/global_details.h
    object/details/jet_flying_details.cpp
    object/details/jet_flying_details.h
    object/details/jostleable_details.cpp
    object/details/jostleable_details.h
    object/details/level_details.cpp
    object/details/level_details.h
    object/details/macro.cpp
    object/details/macro.h
    object/details/modeled_details.cpp
    object/details/modeled_details.h
    object/details/movable_details.cpp
    object/details/movable_details.h
    object/details/naming_details.cpp
    object/details/naming_details.h
    object/details/physical_details.cpp
    object/details/physical_details.h
    object/details/power_container_details.cpp
    object/details/power_container_details.h
    object/details/programmable_details.cpp
    object/details/programmable_details.h
    object/details/ranged_details.cpp
    object/details/ranged_details.h
    object/details/scripting_details.cpp
    object/details/scripting_details.h
    object/details/slotted_details.cpp
    object/details/slotted_details.h
    object/details/shielded_details.cpp
    object/details/shielded_details.h
    object/details/shielded_auto_regen_details.cpp
    object/details/shielded_auto_regen_details.h
    object/details/shielder_details.cpp
    object/details/shielder_details.h
    object/details/task_executor_details.cpp
    object/details/task_executor_details.h
    object/details/thumpable_details.cpp
    object/details/thumpable_details.h
    object/details/trace_drawing_details.cpp
    object/details/trace_drawing_details.h
    object/details/transportable_details.cpp
    object/details/transportable_details.h
    object/hardcode/assistant_hardcode.cpp
    object/hardcode/assistant_hardcode.h
    object/hardcode/automated_hardcode.cpp
    object/hardcode/automated_hardcode.h
    object/hardcode/controllable_hardcode.cpp
    object/hardcode/controllable_hardcode.h
    object/hardcode/damageable_hardcode.cpp
    object/hardcode/damageable_hardcode.h
    object/hardcode/destroyable_hardcode.cpp
    object/hardcode/destroyable_hardcode.h
    object/hardcode/detectable_hardcode.cpp
    object/hardcode/detectable_hardcode.h
    object/hardcode/exchange_post_hardcode.cpp
    object/hardcode/exchange_post_hardcode.h
    object/hardcode/flying_hardcode.cpp
    object/hardcode/flying_hardcode.h
    object/hardcode/fragile_hardcode.cpp
    object/hardcode/fragile_hardcode.h
    object/hardcode/global_hardcode.cpp
    object/hardcode/global_hardcode.h
    object/hardcode/jet_flying_hardcode.cpp
    object/hardcode/jet_flying_hardcode.h
    object/hardcode/jostleable_hardcode.cpp
    object/hardcode/jostleable_hardcode.h
    object/hardcode/modeled_hardcode.cpp
    object/hardcode/modeled_hardcode.h
    object/hardcode/movable_hardcode.cpp
    object/hardcode/movable_hardcode.h
    object/hardcode/naming_hardcode.cpp
    object/hardcode/naming_hardcode.h
    object/hardcode/level_hardcode.cpp
    object/hardcode/level_hardcode.h
    object/hardcode/physical_hardcode.cpp
    object/hardcode/physical_hardcode.h
    object/hardcode/power_container_hardcode.cpp
    object/hardcode/power_container_hardcode.h
    object/hardcode/programmable_hardcode.cpp
    object/hardcode/programmable_hardcode.h
    object/hardcode/ranged_hardcode.cpp
    object/hardcode/ranged_hardcode.h
    object/hardcode/scripting_hardcode.cpp
    object/hardcode/scripting_hardcode.h
    object/hardcode/slotted_hardcode.cpp
    object/hardcode/slotted_hardcode.h
    object/hardcode/shielded_hardcode.cpp
    object/hardcode/shielded_hardcode.h
    object/hardcode/shielded_auto_regen_hardcode.cpp
    object/hardcode/shielded_auto_regen_hardcode.h
    object/hardcode/shielder_hardcode.cpp
    object/hardcode/shielder_hardcode.h
    object/hardcode/task_executor_hardcode.cpp
    object/hardcode/task_executor_hardcode.h
    object/hardcode/thumpable_hardcode.cpp
    object/hardcode/thumpable_hardcode.h
    object/hardcode/trace_drawing_hardcode.cpp
    object/hardcode/trace_drawing_hardcode.h
    object/hardcode/transportable_hardcode.cpp
    object/hardcode/transportable_hardcode.h
    object/helpers/cargo_helpers.cpp
    object/helpers/cargo_helpers.h
    object/helpers/common_helpers.cpp
    object/helpers/common_helpers.h
    object/helpers/level_helpers.cpp
    object/helpers/level_helpers.h
    object/helpers/modeled_helpers.cpp
    object/helpers/modeled_helpers.h
    object/helpers/power_helpers.cpp
    object/helpers/power_helpers.h
    object/helpers/programmable_helpers.cpp
    object/helpers/programmable_helpers.h
    object/implementation/exchange_post_impl.cpp
    object/implementation/exchange_post_impl.h
    object/implementation/power_container_impl.cpp
    object/implementation/power_container_impl.h
    object/implementation/program_storage_impl.cpp
    object/implementation/program_storage_impl.h
    object/implementation/programmable_impl.cpp
    object/implementation/programmable_impl.h
    object/implementation/task_executor_impl.cpp
    object/implementation/task_executor_impl.h
    object/interface/controllable_object.h
    object/interface/damageable_object.h
    object/interface/destroyable_object.h
    object/interface/flying_object.h
    object/interface/fragile_object.h
    object/interface/interactive_object.h
    object/interface/jet_flying_object.h
    object/interface/jostleable_object.h
    object/interface/movable_object.h
    object/interface/modeled_object.h
    object/interface/power_container_object.h
    object/interface/program_storage_object.h
    object/interface/programmable_object.h
    object/interface/ranged_object.h
    object/interface/shielded_auto_regen_object.h
    object/interface/shielded_object.h
    object/interface/shielder_object.h
    object/interface/slotted_object.h
    object/interface/task_executor_object.h
    object/interface/thumpable_object.h
    object/interface/trace_drawing_object.h
    object/interface/transportable_object.h
    object/motion/motion.cpp
    object/motion/motion.h
    object/motion/motionant.cpp
    object/motion/motionant.h
    object/motion/motionbee.cpp
    object/motion/motionbee.h
    object/motion/motionhuman.cpp
    object/motion/motionhuman.h
    object/motion/motionlegged.cpp
    object/motion/motionlegged.h
    object/motion/motionqueen.cpp
    object/motion/motionqueen.h
    object/motion/motionspider.cpp
    object/motion/motionspider.h
    object/motion/motiontoto.cpp
    object/motion/motiontoto.h
    object/motion/motiontracked.cpp
    object/motion/motiontracked.h
    object/motion/motionwheeled.cpp
    object/motion/motionwheeled.h
    object/motion/motionwinged.cpp
    object/motion/motionwinged.h
    object/motion/motionworm.cpp
    object/motion/motionworm.h
    object/object.cpp
    object/object.h
    object/object_create_exception.h
    object/object_create_params.h
    object/object_details.cpp
    object/object_details.h
    object/object_factory.cpp
    object/object_factory.h
    object/object_interface_type.h
    object/object_manager.cpp
    object/object_manager.h
    object/object_part_filter.cpp
    object/object_part_filter.h
    object/object_type.cpp
    object/object_type.h
    object/old_object.cpp
    object/old_object.h
    object/old_object_interface.cpp
    object/old_object_interface.h
    object/subclass/static_object.cpp
    object/subclass/static_object.h
    object/task/task.cpp
    object/task/task.h
    object/task/taskadvance.cpp
    object/task/taskadvance.h
    object/task/taskbuild.cpp
    object/task/taskbuild.h
    object/task/taskdeflag.cpp
    object/task/taskdeflag.h
    object/task/taskdeletemark.cpp
    object/task/taskdeletemark.h
    object/task/taskfire.cpp
    object/task/taskfire.h
    object/task/taskfireant.cpp
    object/task/taskfireant.h
    object/task/taskflag.cpp
    object/task/taskflag.h
    object/task/taskgoto.cpp
    object/task/taskgoto.h
    object/task/taskgungoal.cpp
    object/task/taskgungoal.h
    object/task/taskinfo.cpp
    object/task/taskinfo.h
    object/task/taskmanip.cpp
    object/task/taskmanip.h
    object/task/taskpen.cpp
    object/task/taskpen.h
    object/task/taskrecover.cpp
    object/task/taskrecover.h
    object/task/tasksearch.cpp
    object/task/tasksearch.h
    object/task/taskshield.cpp
    object/task/taskshield.h
    object/task/taskspiderexplo.cpp
    object/task/taskspiderexplo.h
    object/task/tasktake.cpp
    object/task/tasktake.h
    object/task/taskterraform.cpp
    object/task/taskterraform.h
    object/task/taskturn.cpp
    object/task/taskturn.h
    object/task/taskwait.cpp
    object/task/taskwait.h
    physics/physics.cpp
    physics/physics.h
    script/cbottoken.cpp
    script/cbottoken.h
    script/script.cpp
    script/script.h
    script/scriptfunc.cpp
    script/scriptfunc.h
    sound/sound.cpp
    sound/sound.h
    sound/sound_type.cpp
    sound/sound_type.h
    ui/controls/button.cpp
    ui/controls/button.h
    ui/controls/check.cpp
    ui/controls/check.h
    ui/controls/color.cpp
    ui/controls/color.h
    ui/controls/control.cpp
    ui/controls/control.h
    ui/controls/edit.cpp
    ui/controls/edit.h
    ui/controls/editvalue.cpp
    ui/controls/editvalue.h
    ui/controls/enumslider.cpp
    ui/controls/enumslider.h
    ui/controls/gauge.cpp
    ui/controls/gauge.h
    ui/controls/group.cpp
    ui/controls/group.h
    ui/controls/image.cpp
    ui/controls/image.h
    ui/controls/interface.cpp
    ui/controls/interface.h
    ui/controls/key.cpp
    ui/controls/key.h
    ui/controls/label.cpp
    ui/controls/label.h
    ui/controls/list.cpp
    ui/controls/list.h
    ui/controls/logo.cpp
    ui/controls/logo.h
    ui/controls/map.cpp
    ui/controls/map.h
    ui/controls/scroll.cpp
    ui/controls/scroll.h
    ui/controls/shortcut.cpp
    ui/controls/shortcut.h
    ui/controls/slider.cpp
    ui/controls/slider.h
    ui/controls/target.cpp
    ui/controls/target.h
    ui/controls/window.cpp
    ui/controls/window.h
    ui/debug_menu.cpp
    ui/debug_menu.h
    ui/displayinfo.cpp
    ui/displayinfo.h
    ui/displaytext.cpp
    ui/displaytext.h
    ui/filedialog.cpp
    ui/filedialog.h
    ui/maindialog.cpp
    ui/maindialog.h
    ui/mainmap.cpp
    ui/mainmap.h
    ui/mainshort.cpp
    ui/mainshort.h
    ui/mainui.cpp
    ui/mainui.h
    ui/object_interface.cpp
    ui/object_interface.h
    ui/particles_generator.cpp
    ui/particles_generator.h
    ui/screen/screen.cpp
    ui/screen/screen.h
    ui/screen/screen_appearance.cpp
    ui/screen/screen_appearance.h
    ui/screen/screen_io.cpp
    ui/screen/screen_io.h
    ui/screen/screen_io_read.cpp
    ui/screen/screen_io_read.h
    ui/screen/screen_io_write.cpp
    ui/screen/screen_io_write.h
    ui/screen/screen_level_list.cpp
    ui/screen/screen_level_list.h
    ui/screen/screen_loading.cpp
    ui/screen/screen_loading.h
    ui/screen/screen_main_menu.cpp
    ui/screen/screen_main_menu.h
    ui/screen/screen_mod_list.cpp
    ui/screen/screen_mod_list.h
    ui/screen/screen_player_select.cpp
    ui/screen/screen_player_select.h
    ui/screen/screen_quit.cpp
    ui/screen/screen_quit.h
    ui/screen/screen_setup.cpp
    ui/screen/screen_setup.h
    ui/screen/screen_setup_controls.cpp
    ui/screen/screen_setup_controls.h
    ui/screen/screen_setup_display.cpp
    ui/screen/screen_setup_display.h
    ui/screen/screen_setup_game.cpp
    ui/screen/screen_setup_game.h
    ui/screen/screen_setup_graphics.cpp
    ui/screen/screen_setup_graphics.h
    ui/screen/screen_setup_sound.cpp
    ui/screen/screen_setup_sound.h
    ui/screen/screen_welcome.cpp
    ui/screen/screen_welcome.h
    ui/studio.cpp
    ui/studio.h
    ui/widget.h
)

target_include_directories(colobotbase PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/..
    ${CMAKE_CURRENT_BINARY_DIR}
)

# Main libraries
target_link_libraries(colobotbase PUBLIC
    CBot
    localename
    SDL2::Core
    SDL2::Image
    SDL2::TTF
    OpenGL::GL
    PNG::PNG
    GLEW::GLEW
    glm::glm
    Boost::headers
    Boost::filesystem
    Boost::regex
    PhysFS::PhysFS
    SndFile::sndfile
    nlohmann_json::nlohmann_json
)

# Optional libraries
if(OPENAL_SOUND)
    target_sources(colobotbase PRIVATE
        sound/oalsound/alsound.cpp
        sound/oalsound/buffer.cpp
        sound/oalsound/channel.cpp
        sound/oalsound/check.cpp
        sound/oalsound/alsound.h
        sound/oalsound/buffer.h
        sound/oalsound/channel.h
        sound/oalsound/check.h
    )
    target_link_libraries(colobotbase PUBLIC OpenAL::OpenAL)
endif()

if(WINGETOPT)
    target_link_libraries(colobotbase PUBLIC wingetopt)
endif()

# Additional libraries per platform
if(PLATFORM_WINDOWS)
    # because it isn't included in standard linking libraries
    if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        # TODO: this shouldn't be needed, the libraries targets should care of those transitive dependencies
        # This should be treated as a temporary workaround
        if(USE_STATIC_RUNTIME) # Since we're using static runtime, assume every external library is static too
            find_package(Intl REQUIRED)

            find_library(BZ2_LIBRARY NAMES bz2)
            find_library(FREETYPE_LIBRARY NAMES freetype)
            find_library(ICONV_LIBRARY NAMES iconv)
            find_library(CHARSET_LIBRARY NAMES charset)
            find_library(BROTLICOMMON_LIBRARY NAMES brotlicommon-static)
            find_library(BROTLIENC_LIBRARY NAMES brotlienc-static)
            find_library(BROTLIDEC_LIBRARY NAMES brotlidec-static)

            target_link_libraries(colobotbase PUBLIC
                Gettext::Intl
                ${BZ2_LIBRARY}
                ${FREETYPE_LIBRARY}
                ${ICONV_LIBRARY}
                ${CHARSET_LIBRARY}
                ${BROTLICOMMON_LIBRARY}
                ${BROTLIENC_LIBRARY}
                ${BROTLIDEC_LIBRARY}

                # why
                winmm.lib
                dxguid.lib
                imm32.lib
                ole32.lib
                oleaut32.lib
                version.lib
                wsock32.lib
                ws2_32.lib
                setupapi.lib
            )
        endif()
    else()
        target_link_libraries(colobotbase PUBLIC -lintl)
    endif()
elseif(PLATFORM_GNU)
    # nothing
elseif(PLATFORM_LINUX)
    # for clock_gettime
    target_link_libraries(colobotbase PUBLIC -lrt)
elseif(PLATFORM_MACOSX)
    find_package(Intl REQUIRED)
    target_link_libraries(colobotbase PUBLIC Gettext::Intl)
elseif(PLATFORM_FREEBSD)
    find_package(Intl REQUIRED)
    target_link_libraries(colobotbase PUBLIC Gettext::Intl)
endif()


set(COLOBOT_LIBS ${LIBS} PARENT_SCOPE)


# Targets
if(HIDE_CONSOLE)
    add_executable(colobot WIN32 app/main.cpp)
else()
    add_executable(colobot app/main.cpp)
endif()

if(PLATFORM_WINDOWS)
    target_sources(colobot PRIVATE ../desktop/colobot.rc)
endif()

target_link_libraries(colobot colobotbase SDL2::Main)

# Install
install(TARGETS colobot RUNTIME DESTINATION ${COLOBOT_INSTALL_BIN_DIR})
if(MSVC)
    install(FILES $<TARGET_PDB_FILE:colobot> CONFIGURATIONS Debug RelWithDebInfo DESTINATION ${COLOBOT_INSTALL_BIN_DIR} OPTIONAL)
endif()
if(NOT CBOT_STATIC)
    set_target_properties(colobot PROPERTIES INSTALL_RPATH ${COLOBOT_INSTALL_LIB_DIR})
endif()

# Linter-specific
if(COLOBOT_LINT_BUILD)
    add_fake_header_sources("src" colobotbase)
    add_fake_header_sources("src" colobot)
endif()
