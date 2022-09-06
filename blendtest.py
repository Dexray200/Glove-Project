import bpy
import serial
try:
    port = serial.Serial("\\\\.\\COM5", 115200)
except:
    print("Error connecting to port")
    
ADC_RANGE = 255

class ModalTimerOperator(bpy.types.Operator):
    """Operator which runs its self from a timer"""
    bl_idname = "wm.modal_timer_operator"
    bl_label = "Modal Timer Operator"

    _timer = None

    def modal(self, context, event):
        if event.type == 'TIMER':
            if port.in_waiting > 13:
                fingers = port.readline()
                fingers = fingers.decode('UTF-8')
                fingers = fingers.strip()
                print(fingers)
                thumb, index, middle, ring, pinky, sthumb, sindex, smiddle, sring, spinky, analogx, analogy, button, button1, pinch, grab, spiderman, peace = str(fingers).split(':')
                
            else:
                return {'PASS_THROUGH'}
           
            # Gain Data From Glove

            # Move Hand Armetures Using BLE Glove Data
            bpy.data.objects['Armature'].pose.bones['Bone.005'].rotation_quaternion[1] = -(int(thumb))/ADC_RANGE
            bpy.data.objects['Armature'].pose.bones['Bone.012'].rotation_quaternion[3] = (int(index))/ADC_RANGE
            bpy.data.objects['Armature'].pose.bones['Bone.015'].rotation_quaternion[3] = (int(middle))/ADC_RANGE
            bpy.data.objects['Armature'].pose.bones['Bone.017'].rotation_quaternion[3] = (int(ring))/ADC_RANGE
            bpy.data.objects['Armature'].pose.bones['Bone.020'].rotation_quaternion[1] = (int(pinky))/ADC_RANGE
            
            
            bpy.data.objects['Armature'].pose.bones['Bone.006'].rotation_quaternion[1] = -(int(thumb))/ADC_RANGE
            bpy.data.objects['Armature'].pose.bones['Bone.013'].rotation_quaternion[3] = (int(index))/ADC_RANGE
            bpy.data.objects['Armature'].pose.bones['Bone.016'].rotation_quaternion[3] = (int(middle))/ADC_RANGE
            bpy.data.objects['Armature'].pose.bones['Bone.018'].rotation_quaternion[3] = (int(ring))/ADC_RANGE
            bpy.data.objects['Armature'].pose.bones['Bone.021'].rotation_quaternion[1] = (int(pinky))/ADC_RANGE    
             
            bpy.data.objects['Armature'].pose.bones['Bone.005'].rotation_quaternion[3] = -(int(sthumb)-200)/ADC_RANGE
            bpy.data.objects['Armature'].pose.bones['Bone.012'].rotation_quaternion[1] = -(int(spinky))/ADC_RANGE
            bpy.data.objects['Armature'].pose.bones['Bone.015'].rotation_quaternion[1] = -(int(sring))/ADC_RANGE
            bpy.data.objects['Armature'].pose.bones['Bone.017'].rotation_quaternion[1] = -(int(smiddle))/ADC_RANGE
            bpy.data.objects['Armature'].pose.bones['Bone.020'].rotation_quaternion[3] = (int(sindex)-35)/ADC_RANGE
              
        if event.type in {'ESC'}:
            print("Disconnecting Glove")
            port.close()
            return {'CANCELLED'}

        return {'PASS_THROUGH'}

    def execute(self, context):
        wm = context.window_manager
        self._timer = wm.event_timer_add(0.1, window=context.window)
        wm.modal_handler_add(self)
        return {'RUNNING_MODAL'}

    def cancel(self, context):
        wm = context.window_manager
        wm.event_timer_remove(self._timer)


def register():
    bpy.utils.register_class(ModalTimerOperator)


def unregister():
    bpy.utils.unregister_class(ModalTimerOperator)

        
#def NuckleMove(w, x, y, z, keyframe):
#    
#    bpy.data.objects['Armature'].pose.bones['Bone.005'].rotation_quaternion = [w, -z, y, x]
#    bpy.data.objects['Armature'].pose.bones['Bone.005'].keyframe_insert(data_path = 'rotation_quaternion', frame = keyframe)
#    bpy.data.objects['Armature'].pose.bones['Bone.012'].rotation_quaternion = [w, x, y, z]
#    bpy.data.objects['Armature'].pose.bones['Bone.012'].keyframe_insert(data_path = 'rotation_quaternion', frame = keyframe)
#    bpy.data.objects['Armature'].pose.bones['Bone.015'].rotation_quaternion = [w, x, y, z]
#    bpy.data.objects['Armature'].pose.bones['Bone.015'].keyframe_insert(data_path = 'rotation_quaternion', frame = keyframe)
#    bpy.data.objects['Armature'].pose.bones['Bone.017'].rotation_quaternion = [w, x, y, z]
#    bpy.data.objects['Armature'].pose.bones['Bone.017'].keyframe_insert(data_path = 'rotation_quaternion', frame = keyframe)
#    bpy.data.objects['Armature'].pose.bones['Bone.020'].rotation_quaternion = [w, z, y, x]
#    bpy.data.objects['Armature'].pose.bones['Bone.020'].keyframe_insert(data_path = 'rotation_quaternion', frame = keyframe)
#      
#def pipJoint(w, x, y, z, keyframe):
#    
#    bpy.data.objects['Armature'].pose.bones['Bone.006'].rotation_quaternion = [w, -z, y, x]
#    bpy.data.objects['Armature'].pose.bones['Bone.006'].keyframe_insert(data_path = 'rotation_quaternion', frame = keyframe)
#    bpy.data.objects['Armature'].pose.bones['Bone.013'].rotation_quaternion = [w, x, y, z]
#    bpy.data.objects['Armature'].pose.bones['Bone.013'].keyframe_insert(data_path = 'rotation_quaternion', frame = keyframe)
#    bpy.data.objects['Armature'].pose.bones['Bone.016'].rotation_quaternion = [w, x, y, z]
#    bpy.data.objects['Armature'].pose.bones['Bone.016'].keyframe_insert(data_path = 'rotation_quaternion', frame = keyframe)
#    bpy.data.objects['Armature'].pose.bones['Bone.018'].rotation_quaternion = [w, x, y, z]
#    bpy.data.objects['Armature'].pose.bones['Bone.018'].keyframe_insert(data_path = 'rotation_quaternion', frame = keyframe)
#    bpy.data.objects['Armature'].pose.bones['Bone.021'].rotation_quaternion = [w, z, y, x]
#    bpy.data.objects['Armature'].pose.bones['Bone.021'].keyframe_insert(data_path = 'rotation_quaternion', frame = keyframe)

#def splayMove(value, keyframe):
#    bpy.data.objects['Armature'].pose.bones['Bone.005'].rotation_quaternion[3] = -value
#    bpy.data.objects['Armature'].pose.bones['Bone.005'].keyframe_insert(data_path = 'rotation_quaternion', frame = keyframe)
#    bpy.data.objects['Armature'].pose.bones['Bone.012'].rotation_quaternion[1] = value
#    bpy.data.objects['Armature'].pose.bones['Bone.012'].keyframe_insert(data_path = 'rotation_quaternion', frame = keyframe)
#    bpy.data.objects['Armature'].pose.bones['Bone.017'].rotation_quaternion[1] = -value 
#    bpy.data.objects['Armature'].pose.bones['Bone.017'].keyframe_insert(data_path = 'rotation_quaternion', frame = keyframe)
#    bpy.data.objects['Armature'].pose.bones['Bone.020'].rotation_quaternion[3] = value
#    bpy.data.objects['Armature'].pose.bones['Bone.020'].keyframe_insert(data_path = 'rotation_quaternion', frame = keyframe)


if __name__ == "__main__":
    register()

    # test call
    bpy.ops.wm.modal_timer_operator()
