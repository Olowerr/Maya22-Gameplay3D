#-------------------------------------------------
#
# Project created by QtCreator
#
#-------------------------------------------------
QT -= core gui
TARGET = gameplay
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11
CONFIG -= qt
CONFIG(debug, debug|release): DEFINES += _DEBUG

SOURCES += src/AbsoluteLayout.cpp \
    src/AIAgent.cpp \
    src/AIController.cpp \
    src/AIMessage.cpp \
    src/AIState.cpp \
    src/AIStateMachine.cpp \
    src/Animation.cpp \
    src/AnimationClip.cpp \
    src/AnimationController.cpp \
    src/AnimationTarget.cpp \
    src/AnimationValue.cpp \
    src/AudioBuffer.cpp \
    src/AudioController.cpp \
    src/AudioListener.cpp \
    src/AudioSource.cpp \
    src/BoundingBox.cpp \
    src/BoundingBox.inl \
    src/BoundingSphere.cpp \
    src/BoundingSphere.inl \
    src/Bundle.cpp \
    src/Button.cpp \
    src/Camera.cpp \
    src/CheckBox.cpp \
    src/Container.cpp \
    src/Control.cpp \
    src/ControlFactory.cpp \
    src/Curve.cpp \
    src/DepthStencilTarget.cpp \
    src/Drawable.cpp \
    src/Effect.cpp \
    src/FileSystem.cpp \
    src/FlowLayout.cpp \
    src/Font.cpp \
    src/Form.cpp \
    src/FrameBuffer.cpp \
    src/Frustum.cpp \
    src/Game.cpp \
    src/Game.inl \
    src/Gamepad.cpp \
    src/HeightField.cpp \
    src/Image.cpp \
    src/Image.inl \
    src/ImageControl.cpp \
    src/Joint.cpp \
    src/JoystickControl.cpp \
    src/Label.cpp \
    src/Layout.cpp \
    src/Light.cpp \
    src/Logger.cpp \
    src/Material.cpp \
    src/MaterialParameter.cpp \
    src/MathUtil.cpp \
    src/MathUtil.inl \
    src/MathUtilNeon.inl \
    src/Matrix.cpp \
    src/Matrix.inl \
    src/Mesh.cpp \
    src/MeshBatch.cpp \
    src/MeshBatch.inl \
    src/MeshPart.cpp \
    src/MeshSkin.cpp \
    src/Model.cpp \
    src/Node.cpp \
    src/ParticleEmitter.cpp \
    src/Pass.cpp \
    src/PhysicsCharacter.cpp \
    src/PhysicsCollisionObject.cpp \
    src/PhysicsCollisionShape.cpp \
    src/PhysicsConstraint.cpp \
    src/PhysicsConstraint.inl \
    src/PhysicsController.cpp \
    src/PhysicsFixedConstraint.cpp \
    src/PhysicsFixedConstraint.inl \
    src/PhysicsGenericConstraint.cpp \
    src/PhysicsGenericConstraint.inl \
    src/PhysicsGhostObject.cpp \
    src/PhysicsHingeConstraint.cpp \
    src/PhysicsRigidBody.cpp \
    src/PhysicsRigidBody.inl \
    src/PhysicsSocketConstraint.cpp \
    src/PhysicsSpringConstraint.cpp \
    src/PhysicsSpringConstraint.inl \
    src/PhysicsVehicle.cpp \
    src/PhysicsVehicleWheel.cpp \
    src/Plane.cpp \
    src/Plane.inl \
    src/Platform.cpp \
    src/Properties.cpp \
    src/Quaternion.cpp \
    src/Quaternion.inl \
    src/RadioButton.cpp \
    src/Ray.cpp \
    src/Ray.inl \
    src/Rectangle.cpp \
    src/Ref.cpp \
    src/RenderState.cpp \
    src/RenderTarget.cpp \
    src/Scene.cpp \
    src/SceneLoader.cpp \
    src/ScreenDisplayer.cpp \
    src/Script.cpp \
    src/ScriptController.cpp \
    src/ScriptController.inl \
    src/ScriptTarget.cpp \
    src/Slider.cpp \
    src/Sprite.cpp \
    src/SpriteBatch.cpp \
    src/Technique.cpp \
    src/Terrain.cpp \
    src/TerrainPatch.cpp \
    src/Text.cpp \
    src/TextBox.cpp \
    src/Texture.cpp \
    src/Theme.cpp \
    src/ThemeStyle.cpp \
    src/TileSet.cpp \
    src/Transform.cpp \
    src/Vector2.cpp \
    src/Vector2.inl \
    src/Vector3.cpp \
    src/Vector3.inl \
    src/Vector4.cpp \
    src/Vector4.inl \
    src/VertexAttributeBinding.cpp \
    src/VertexFormat.cpp \
    src/VerticalLayout.cpp \
    src/lua/lua_all_bindings.cpp \
    src/lua/lua_AbsoluteLayout.cpp \
    src/lua/lua_AIAgent.cpp \
    src/lua/lua_AIAgentListener.cpp \
    src/lua/lua_AIController.cpp \
    src/lua/lua_AIMessage.cpp \
    src/lua/lua_AIState.cpp \
    src/lua/lua_AIStateListener.cpp \
    src/lua/lua_AIStateMachine.cpp \
    src/lua/lua_Animation.cpp \
    src/lua/lua_AnimationClip.cpp \
    src/lua/lua_AnimationClipListener.cpp \
    src/lua/lua_AnimationController.cpp \
    src/lua/lua_AnimationTarget.cpp \
    src/lua/lua_AnimationValue.cpp \
    src/lua/lua_AudioBuffer.cpp \
    src/lua/lua_AudioController.cpp \
    src/lua/lua_AudioListener.cpp \
    src/lua/lua_AudioSource.cpp \
    src/lua/lua_BoundingBox.cpp \
    src/lua/lua_BoundingSphere.cpp \
    src/lua/lua_Bundle.cpp \
    src/lua/lua_Button.cpp \
    src/lua/lua_Camera.cpp \
    src/lua/lua_CameraListener.cpp \
    src/lua/lua_CheckBox.cpp \
    src/lua/lua_Container.cpp \
    src/lua/lua_Control.cpp \
    src/lua/lua_ControlListener.cpp \
    src/lua/lua_Curve.cpp \
    src/lua/lua_DepthStencilTarget.cpp \
    src/lua/lua_Drawable.cpp \
    src/lua/lua_Effect.cpp \
    src/lua/lua_FileSystem.cpp \
    src/lua/lua_FlowLayout.cpp \
    src/lua/lua_Font.cpp \
    src/lua/lua_Form.cpp \
    src/lua/lua_FrameBuffer.cpp \
    src/lua/lua_Frustum.cpp \
    src/lua/lua_Game.cpp \
    src/lua/lua_Gamepad.cpp \
    src/lua/lua_Gesture.cpp \
    src/lua/lua_Global.cpp \
    src/lua/lua_HeightField.cpp \
    src/lua/lua_Image.cpp \
    src/lua/lua_ImageControl.cpp \
    src/lua/lua_Joint.cpp \
    src/lua/lua_JoystickControl.cpp \
    src/lua/lua_Keyboard.cpp \
    src/lua/lua_Label.cpp \
    src/lua/lua_Layout.cpp \
    src/lua/lua_Light.cpp \
    src/lua/lua_Logger.cpp \
    src/lua/lua_Material.cpp \
    src/lua/lua_MaterialParameter.cpp \
    src/lua/lua_MathUtil.cpp \
    src/lua/lua_Matrix.cpp \
    src/lua/lua_Mesh.cpp \
    src/lua/lua_MeshBatch.cpp \
    src/lua/lua_MeshPart.cpp \
    src/lua/lua_MeshSkin.cpp \
    src/lua/lua_Model.cpp \
    src/lua/lua_Mouse.cpp \
    src/lua/lua_Node.cpp \
    src/lua/lua_NodeCloneContext.cpp \
    src/lua/lua_ParticleEmitter.cpp \
    src/lua/lua_Pass.cpp \
    src/lua/lua_PhysicsCharacter.cpp \
    src/lua/lua_PhysicsCollisionObject.cpp \
    src/lua/lua_PhysicsCollisionObjectCollisionListener.cpp \
    src/lua/lua_PhysicsCollisionObjectCollisionPair.cpp \
    src/lua/lua_PhysicsCollisionShape.cpp \
    src/lua/lua_PhysicsCollisionShapeDefinition.cpp \
    src/lua/lua_PhysicsConstraint.cpp \
    src/lua/lua_PhysicsController.cpp \
    src/lua/lua_PhysicsControllerHitFilter.cpp \
    src/lua/lua_PhysicsControllerHitResult.cpp \
    src/lua/lua_PhysicsControllerListener.cpp \
    src/lua/lua_PhysicsFixedConstraint.cpp \
    src/lua/lua_PhysicsGenericConstraint.cpp \
    src/lua/lua_PhysicsGhostObject.cpp \
    src/lua/lua_PhysicsHingeConstraint.cpp \
    src/lua/lua_PhysicsRigidBody.cpp \
    src/lua/lua_PhysicsRigidBodyParameters.cpp \
    src/lua/lua_PhysicsSocketConstraint.cpp \
    src/lua/lua_PhysicsSpringConstraint.cpp \
    src/lua/lua_PhysicsVehicle.cpp \
    src/lua/lua_PhysicsVehicleWheel.cpp \
    src/lua/lua_Plane.cpp \
    src/lua/lua_Platform.cpp \
    src/lua/lua_Properties.cpp \
    src/lua/lua_Quaternion.cpp \
    src/lua/lua_RadioButton.cpp \
    src/lua/lua_Ray.cpp \
    src/lua/lua_Rectangle.cpp \
    src/lua/lua_Ref.cpp \
    src/lua/lua_RenderState.cpp \
    src/lua/lua_RenderStateStateBlock.cpp \
    src/lua/lua_RenderTarget.cpp \
    src/lua/lua_Scene.cpp \
    src/lua/lua_ScreenDisplayer.cpp \
    src/lua/lua_Script.cpp \
    src/lua/lua_ScriptController.cpp \
    src/lua/lua_ScriptTarget.cpp \
    src/lua/lua_ScriptTargetEvent.cpp \
    src/lua/lua_ScriptTargetEventRegistry.cpp \
    src/lua/lua_Slider.cpp \
    src/lua/lua_Sprite.cpp \
    src/lua/lua_SpriteBatch.cpp \
    src/lua/lua_SpriteBatchSpriteVertex.cpp \
    src/lua/lua_Technique.cpp \
    src/lua/lua_Terrain.cpp \
    src/lua/lua_TerrainPatch.cpp \
    src/lua/lua_Text.cpp \
    src/lua/lua_TextBox.cpp \
    src/lua/lua_Texture.cpp \
    src/lua/lua_TextureSampler.cpp \
    src/lua/lua_Theme.cpp \
    src/lua/lua_ThemeSideRegions.cpp \
    src/lua/lua_ThemeStyle.cpp \
    src/lua/lua_ThemeThemeImage.cpp \
    src/lua/lua_ThemeUVs.cpp \
    src/lua/lua_TileSet.cpp \
    src/lua/lua_Touch.cpp \
    src/lua/lua_Transform.cpp \
    src/lua/lua_TransformListener.cpp \
    src/lua/lua_Uniform.cpp \
    src/lua/lua_Vector2.cpp \
    src/lua/lua_Vector3.cpp \
    src/lua/lua_Vector4.cpp \
    src/lua/lua_VertexAttributeBinding.cpp \
    src/lua/lua_VertexFormat.cpp \
    src/lua/lua_VertexFormatElement.cpp \
    src/lua/lua_VerticalLayout.cpp

HEADERS += src/AbsoluteLayout.h \
    src/AIAgent.h \
    src/AIController.h \
    src/AIMessage.h \
    src/AIState.h \
    src/AIStateMachine.h \
    src/Animation.h \
    src/AnimationClip.h \
    src/AnimationController.h \
    src/AnimationTarget.h \
    src/AnimationValue.h \
    src/AudioBuffer.h \
    src/AudioController.h \
    src/AudioListener.h \
    src/AudioSource.h \
    src/Base.h \
    src/BoundingBox.h \
    src/BoundingSphere.h \
    src/Bundle.h \
    src/Button.h \
    src/Camera.h \
    src/CheckBox.h \
    src/Container.h \
    src/Control.h \
    src/ControlFactory.h \
    src/Curve.h \
    src/DepthStencilTarget.h \
    src/Drawable.h \
    src/Effect.h \
    src/FileSystem.h \
    src/FlowLayout.h \
    src/Font.h \
    src/Form.h \
    src/FrameBuffer.h \
    src/Frustum.h \
    src/Game.h \
    src/Gamepad.h \
    src/gameplay.h \
    src/Gesture.h \
    src/HeightField.h \
    src/Image.h \
    src/ImageControl.h \
    src/Joint.h \
    src/JoystickControl.h \
    src/Keyboard.h \
    src/Label.h \
    src/Layout.h \
    src/Light.h \
    src/Logger.h \
    src/Material.h \
    src/MaterialParameter.h \
    src/MathUtil.h \
    src/Matrix.h \
    src/Mesh.h \
    src/MeshBatch.h \
    src/MeshPart.h \
    src/MeshSkin.h \
    src/Model.h \
    src/Mouse.h \
    src/Node.h \
    src/ParticleEmitter.h \
    src/Pass.h \
    src/PhysicsCharacter.h \
    src/PhysicsCollisionObject.h \
    src/PhysicsCollisionShape.h \
    src/PhysicsConstraint.h \
    src/PhysicsController.h \
    src/PhysicsFixedConstraint.h \
    src/PhysicsGenericConstraint.h \
    src/PhysicsGhostObject.h \
    src/PhysicsHingeConstraint.h \
    src/PhysicsRigidBody.h \
    src/PhysicsSocketConstraint.h \
    src/PhysicsSpringConstraint.h \
    src/PhysicsVehicle.h \
    src/PhysicsVehicleWheel.h \
    src/Plane.h \
    src/Platform.h \
    src/Properties.h \
    src/Quaternion.h \
    src/RadioButton.h \
    src/Ray.h \
    src/Rectangle.h \
    src/Ref.h \
    src/RenderState.h \
    src/RenderTarget.h \
    src/Scene.h \
    src/SceneLoader.h \
    src/ScreenDisplayer.h \
    src/Script.h \
    src/ScriptController.h \
    src/ScriptTarget.h \
    src/Slider.h \
    src/Sprite.h \
    src/SpriteBatch.h \
    src/Stream.h \
    src/Technique.h \
    src/Terrain.h \
    src/TerrainPatch.h \
    src/Text.h \
    src/TextBox.h \
    src/Texture.h \
    src/Theme.h \
    src/ThemeStyle.h \
    src/TileSet.h \
    src/TimeListener.h \
    src/Touch.h \
    src/Transform.h \
    src/Vector2.h \
    src/Vector3.h \
    src/Vector4.h \
    src/VertexAttributeBinding.h \
    src/VertexFormat.h \
    src/VerticalLayout.h \
    src/lua/lua_AbsoluteLayout.h \
    src/lua/lua_AIAgent.h \
    src/lua/lua_AIAgentListener.h \
    src/lua/lua_AIController.h \
    src/lua/lua_AIMessage.h \
    src/lua/lua_AIState.h \
    src/lua/lua_AIStateListener.h \
    src/lua/lua_AIStateMachine.h \
    src/lua/lua_all_bindings.h \
    src/lua/lua_Animation.h \
    src/lua/lua_AnimationClip.h \
    src/lua/lua_AnimationClipListener.h \
    src/lua/lua_AnimationController.h \
    src/lua/lua_AnimationTarget.h \
    src/lua/lua_AnimationValue.h \
    src/lua/lua_AudioBuffer.h \
    src/lua/lua_AudioController.h \
    src/lua/lua_AudioListener.h \
    src/lua/lua_AudioSource.h \
    src/lua/lua_BoundingBox.h \
    src/lua/lua_BoundingSphere.h \
    src/lua/lua_Bundle.h \
    src/lua/lua_Button.h \
    src/lua/lua_Camera.h \
    src/lua/lua_CameraListener.h \
    src/lua/lua_CheckBox.h \
    src/lua/lua_Container.h \
    src/lua/lua_Control.h \
    src/lua/lua_ControlListener.h \
    src/lua/lua_Curve.h \
    src/lua/lua_DepthStencilTarget.h \
    src/lua/lua_Drawable.h \
    src/lua/lua_Effect.h \
    src/lua/lua_FileSystem.h \
    src/lua/lua_FlowLayout.h \
    src/lua/lua_Font.h \
    src/lua/lua_Form.h \
    src/lua/lua_FrameBuffer.h \
    src/lua/lua_Frustum.h \
    src/lua/lua_Game.h \
    src/lua/lua_Gamepad.h \
    src/lua/lua_Gesture.h \
    src/lua/lua_Global.h \
    src/lua/lua_HeightField.h \
    src/lua/lua_Image.h \
    src/lua/lua_ImageControl.h \
    src/lua/lua_ImageFormat.h \
    src/lua/lua_Joint.h \
    src/lua/lua_JoystickControl.h \
    src/lua/lua_Keyboard.h \
    src/lua/lua_Label.h \
    src/lua/lua_Layout.h \
    src/lua/lua_Light.h \
    src/lua/lua_Logger.h \
    src/lua/lua_Material.h \
    src/lua/lua_MaterialParameter.h \
    src/lua/lua_MathUtil.h \
    src/lua/lua_Matrix.h \
    src/lua/lua_Mesh.h \
    src/lua/lua_MeshBatch.h \
    src/lua/lua_MeshPart.h \
    src/lua/lua_MeshSkin.h \
    src/lua/lua_Model.h \
    src/lua/lua_Mouse.h \
    src/lua/lua_Node.h \
    src/lua/lua_NodeCloneContext.h \
    src/lua/lua_ParticleEmitter.h \
    src/lua/lua_Pass.h \
    src/lua/lua_PhysicsCharacter.h \
    src/lua/lua_PhysicsCollisionObject.h \
    src/lua/lua_PhysicsCollisionObjectCollisionListener.h \
    src/lua/lua_PhysicsCollisionObjectCollisionPair.h \
    src/lua/lua_PhysicsCollisionObjectType.h \
    src/lua/lua_PhysicsCollisionShape.h \
    src/lua/lua_PhysicsCollisionShapeDefinition.h \
    src/lua/lua_PhysicsConstraint.h \
    src/lua/lua_PhysicsController.h \
    src/lua/lua_PhysicsControllerHitFilter.h \
    src/lua/lua_PhysicsControllerHitResult.h \
    src/lua/lua_PhysicsControllerListener.h \
    src/lua/lua_PhysicsFixedConstraint.h \
    src/lua/lua_PhysicsGenericConstraint.h \
    src/lua/lua_PhysicsGhostObject.h \
    src/lua/lua_PhysicsHingeConstraint.h \
    src/lua/lua_PhysicsRigidBody.h \
    src/lua/lua_PhysicsRigidBodyParameters.h \
    src/lua/lua_PhysicsSocketConstraint.h \
    src/lua/lua_PhysicsSpringConstraint.h \
    src/lua/lua_PhysicsVehicle.h \
    src/lua/lua_PhysicsVehicleWheel.h \
    src/lua/lua_Plane.h \
    src/lua/lua_Platform.h \
    src/lua/lua_Properties.h \
    src/lua/lua_Quaternion.h \
    src/lua/lua_RadioButton.h \
    src/lua/lua_Ray.h \
    src/lua/lua_Rectangle.h \
    src/lua/lua_Ref.h \
    src/lua/lua_RenderState.h \
    src/lua/lua_RenderTarget.h \
    src/lua/lua_Scene.h \
    src/lua/lua_ScreenDisplayer.h \
    src/lua/lua_Script.h \
    src/lua/lua_ScriptController.h \
    src/lua/lua_ScriptTarget.h \
    src/lua/lua_ScriptTargetEvent.h \
    src/lua/lua_ScriptTargetEventRegistry.h \
    src/lua/lua_Slider.h \
    src/lua/lua_Sprite.h \
    src/lua/lua_SpriteBatch.h \
    src/lua/lua_SpriteBatchSpriteVertex.h \
    src/lua/lua_Technique.h \
    src/lua/lua_Terrain.h \
    src/lua/lua_TerrainPatch.h \
    src/lua/lua_Text.h \
    src/lua/lua_TextBox.h \
    src/lua/lua_Texture.h \
    src/lua/lua_TextureSampler.h \
    src/lua/lua_Theme.h \
    src/lua/lua_ThemeSideRegions.h \
    src/lua/lua_ThemeStyle.h \
    src/lua/lua_ThemeThemeImage.h \
    src/lua/lua_ThemeUVs.h \
    src/lua/lua_TileSet.h \
    src/lua/lua_Touch.h \
    src/lua/lua_TouchTouchEvent.h \
    src/lua/lua_Transform.h \
    src/lua/lua_TransformListener.h \
    src/lua/lua_Uniform.h \
    src/lua/lua_Vector2.h \
    src/lua/lua_Vector3.h \
    src/lua/lua_Vector4.h \
    src/lua/lua_VertexAttributeBinding.h \
    src/lua/lua_VertexFormat.h \
    src/lua/lua_VertexFormatElement.h \
    src/lua/lua_VerticalLayout.h

INCLUDEPATH += $$PWD/../gameplay/src
INCLUDEPATH += $$PWD/../external-deps/include
DEFINES += GP_USE_GAMEPAD

linux: SOURCES += src/PlatformLinux.cpp
linux: SOURCES += src/gameplay-main-linux.cpp
linux: QMAKE_CXXFLAGS += -lstdc++ -pthread -w
linux: DEFINES += __linux__
linux: INCLUDEPATH += /usr/include/gtk-2.0
linux: INCLUDEPATH += /usr/lib/x86_64-linux-gnu/gtk-2.0/include
linux: INCLUDEPATH += /usr/include/atk-1.0
linux: INCLUDEPATH += /usr/include/cairo
linux: INCLUDEPATH += /usr/include/gdk-pixbuf-2.0
linux: INCLUDEPATH += /usr/include/pango-1.0
linux: INCLUDEPATH += /usr/include/gio-unix-2.0
linux: INCLUDEPATH += /usr/include/freetype2
linux: INCLUDEPATH += /usr/include/glib-2.0
linux: INCLUDEPATH += /usr/lib/x86_64-linux-gnu/glib-2.0/include
linux: INCLUDEPATH += /usr/include/pixman-1
linux: INCLUDEPATH += /usr/include/libpng12
linux: INCLUDEPATH += /usr/include/harfbuzz

macx: OBJECTIVE_SOURCES += src/PlatformMacOSX.mm
macx: OBJECTIVE_SOURCES += src/gameplay-main-macosx.mm
macx: QMAKE_CXXFLAGS += -x c++ -x objective-c++ -stdlib=libc++ -w -arch x86_64
macx: LIBS += -F/System/Library/Frameworks -framework GameKit
macx: LIBS += -F/System/Library/Frameworks -framework IOKit
macx: LIBS += -F/System/Library/Frameworks -framework QuartzCore
macx: LIBS += -F/System/Library/Frameworks -framework OpenAL
macx: LIBS += -F/System/Library/Frameworks -framework OpenGL
macx: LIBS += -F/System/Library/Frameworks -framework Cocoa
macx: LIBS += -F/System/Library/Frameworks -framework Foundation

win32: SOURCES += src/PlatformWindows.cpp
win32: SOURCES += src/gameplay-main-windows.cpp
win32: DEFINES += WIN32 _UNICODE UNICODE
win32: INCLUDEPATH += $$(DXSDK_DIR)/Include
win32: QMAKE_CXXFLAGS_WARN_ON -= -w34100
win32: QMAKE_CXXFLAGS_WARN_ON -= -w34189
win32: QMAKE_CXXFLAGS_WARN_ON -= -w4302
