import serial
import threading
import cv2
from deepface import DeepFace
import tkinter as tk
from tkinter import messagebox
from pathlib import Path
import os


# Global variables =========================================================================================================
loop = True

p_state = 0;
s_state = 0;
m_state = 0;


# Tkinter code =============================================================================================================
# Button functions for PinPage
def send_pin():
    entered_pin = "p" + PinEntry.get() + "\n"
    ser.write(entered_pin.encode('utf-8'))

# Button functions for SettingPage
def exit():
    close_SettingPage()
      
def shutdown():
    global loop
    loop = False
      
def disarm():
    dis = "d\n"
    ser.write(dis.encode('utf-8'))
      
def runtest():
    test = "r\n"
    ser.write(test.encode('utf-8'))

def delface():
    folder_path = r"/home/willnatsan/uni/acs233-burglar-alarm/pics"
    os.system(f'explorer {folder_path}')
      
def regface():
    folder_path = r"/home/willnatsan/uni/acs233-burglar-alarm/pics"
    os.system(f'explorer {folder_path}')
      
def changepin():
    newpin = "r" + ChangePinEntry.get() + "\n"
    ser.write(newpin.encode('utf-8'))

def disarmedstate():
    state = "sd\n"
    ser.write(state.encode('utf-8'))

def homestate():
    state = "sh\n"
    ser.write(state.encode('utf-8'))

def awaystate():
    state = "sa\n"
    ser.write(state.encode('utf-8'))

# General button functions
def open_SettingPage():
    PinPage.withdraw()  # Hide the first window
    SettingPage.deiconify()  # Show the second window

def close_SettingPage():
    SettingPage.withdraw()  # Hide the second window
    PinPage.deiconify()  # Show the first window
    PinEntry.delete(0, 'end')  # Clear the password entry field
    
def display_state():
    if p_state:
        pir_state.config(bg="#e6695b")
    else:
        pir_state.config(bg="#00FFC7")
        
    if m_state:
        mag_state.config(bg="#e6695b")
    else:
        mag_state.config(bg="#00FFC7")
        
    if s_state:
        sol_state.config(bg="#e6695b")
    else:
        sol_state.config(bg="#00FFC7")
    
    

# PinPage window
PinPage = tk.Tk()
PinPage.title("PIN Page")
PinPage.geometry('640x480')
PinPage.grid_propagate(False)
for x in range(32):
  tk.Grid.columnconfigure(PinPage, x, weight=1, uniform='row')
  tk.Label(PinPage, width = 1, bg = '#101f2d').grid(row = 0, column = x, sticky = "NSEW")
for y in range(24):
  tk.Grid.rowconfigure(PinPage, y, weight=1, uniform='row')
  tk.Label(PinPage, width = 1, bg = '#101f2d').grid(row = y, column = 0, sticky = "NSEW")
PinPage.configure(background='#101f2d')
PinPage.resizable(False, False)

PinEntryLabel = tk.Label(PinPage, text = "Enter PIN:", font = ('Consolas', 26), width = 1, height = 1, fg = '#000000', bg = '#3a5a78')
PinEntryLabel.grid(row = 0, column = 0, columnspan = 32, rowspan = 7, sticky = "NSEW")

PinEntry = tk.Entry(PinPage, width = 1, bg = '#FFFFFF', font = ('Consolas', 22), justify = 'center')
PinEntry.grid(row = 11, column = 3, columnspan = 26, rowspan = 3, sticky = "NSEW")
PinEntry.insert(0, "")

PinEnteryButton = tk.Button(PinPage, text = "Enter", font = ('Consolas', 22), width = 1, height = 1, fg = '#000000', command = send_pin, bg = '#3a5a78')
PinEnteryButton.grid(row = 16, column = 11, columnspan = 10, rowspan = 3, sticky = "NSEW")


# SettingPage window
SettingPage = tk.Toplevel()
SettingPage.title("Setting Page")
SettingPage.geometry('1280x720')
SettingPage.grid_propagate(False)
for x in range(64):
  tk.Grid.columnconfigure(SettingPage, x, weight=1, uniform='row')
  tk.Label(SettingPage, width = 1, bg = '#101f2d').grid(row = 0, column = x, sticky = "NSEW")
for y in range(36):
  tk.Grid.rowconfigure(SettingPage, y, weight=1, uniform='row')
  tk.Label(SettingPage, width = 1, bg = '#101f2d').grid(row = y, column = 0, sticky = "NSEW")
SettingPage.configure(background='#101f2d')
SettingPage.resizable(False, False)

TopPanelLabel = tk.Label(SettingPage, text = "Configuration Panel", font = ('Consolas', 26), width = 1, height = 1, fg = '#000000', bg = '#3a5a78')
TopPanelLabel.grid(row = 0, column = 0, columnspan = 64, rowspan = 4, sticky = "NSEW")
StateLabel = tk.Label(SettingPage, text = "Operational State:", font = ('Consolas', 18), width = 1, height = 1, fg = '#000000', bg = '#3a5a78')
StateLabel.grid(row = 5, column = 3, columnspan = 10, rowspan = 3, sticky = "NSEW")
ChangePinLabel = tk.Label(SettingPage, text = "Change Pin:", font = ('Consolas', 18), width = 1, height = 1, fg = '#000000', bg = '#3a5a78')
ChangePinLabel.grid(row = 5, column = 19, columnspan = 10, rowspan = 3, sticky = "NSEW")
RegFaceLabel = tk.Label(SettingPage, text = "Register Face:", font = ('Consolas', 18), width = 1, height = 1, fg = '#000000', bg = '#3a5a78')
RegFaceLabel.grid(row = 5, column = 35, columnspan = 10, rowspan = 3, sticky = "NSEW")
DelFaceLabel = tk.Label(SettingPage, text = "Delete Face:", font = ('Consolas', 18), width = 1, height = 1, fg = '#000000', bg = '#3a5a78')
DelFaceLabel.grid(row = 5, column = 51, columnspan = 10, rowspan = 3, sticky = "NSEW")
split_1 = tk.Label(SettingPage, text = "", font = ('Arial', 16), width = 1, height = 1, fg = '#000000', bg = '#3a5a78')
split_1.grid(row = 19, column = 0, columnspan = 64, rowspan = 2, sticky = "NSEW")
split_2 = tk.Label(SettingPage, text = "", font = ('Arial', 16), width = 1, height = 1, fg = '#000000', bg = '#3a5a78')
split_2.grid(row = 28, column = 0, columnspan = 64, rowspan = 2, sticky = "NSEW")
sensor_state = tk.Label(SettingPage, text = "State:", font = ('Consolas', 18), width = 1, height = 1, fg = '#000000', bg = '#3a5a78')
sensor_state.grid(row = 23, column = 4, columnspan = 8, rowspan = 3, sticky = "NSEW")
pir_state = tk.Label(SettingPage, text = "PIR State", font = ('Consolas', 18), width = 1, height = 1, fg = '#000000', bg = '#00FFC7')
pir_state.grid(row = 23, column = 20, columnspan = 8, rowspan = 3, sticky = "NSEW")
mag_state = tk.Label(SettingPage, text = "Mag State", font = ('Consolas', 18), width = 1, height = 1, fg = '#000000', bg = '#00FFC7')
mag_state.grid(row = 23, column = 36, columnspan = 8, rowspan = 3, sticky = "NSEW")
sol_state = tk.Label(SettingPage, text = "Solenoid State", font = ('Consolas', 18), width = 1, height = 1, fg = '#000000', bg = '#00FFC7')
sol_state.grid(row = 23, column = 52, columnspan = 8, rowspan = 3, sticky = "NSEW")

ChangePinEntry = tk.Entry(SettingPage, width = 1, bg = '#FFFFFF', font = ('Consolas', 16), justify = 'center')
ChangePinEntry.grid(row = 10, column = 20, columnspan = 8, rowspan = 2, sticky = "NSEW")
ChangePinEntry.insert(0, "")

ExitButton = tk.Button(SettingPage, text = "Exit", font = ('Consolas', 18), width = 1, height = 1, fg = '#000000', command = exit, bg = '#e6695b')
ExitButton.grid(row = 31, column = 54, columnspan = 7, rowspan = 4, sticky = "NSEW")
ShutDownButton = tk.Button(SettingPage, text = "Shutdown", font = ('Consolas', 18), width = 1, height = 1, fg = '#000000', command = shutdown, bg = '#e6695b')
ShutDownButton.grid(row = 31, column = 44, columnspan = 7, rowspan = 4, sticky = "NSEW")
DisarmButton = tk.Button(SettingPage, text = "Disarm", font = ('Consolas', 18), width = 1, height = 1, fg = '#000000', command = disarm, bg = '#e6695b')
DisarmButton.grid(row = 31, column = 34, columnspan = 7, rowspan = 4, sticky = "NSEW")
RunTestButton = tk.Button(SettingPage, text = "Run Test", font = ('Consolas', 18), width = 1, height = 1, fg = '#000000', command = runtest, bg = '#668db2')
RunTestButton.grid(row = 31, column = 3, columnspan = 7, rowspan = 4, sticky = "NSEW")
DeleteFaceButton = tk.Button(SettingPage, text = "Delete", font = ('Consolas', 16), width = 1, height = 1, fg = '#000000', command = delface, bg = '#668db2')
DeleteFaceButton.grid(row = 10, column = 52, columnspan = 8, rowspan = 2, sticky = "NSEW")
RegisterFaceButton = tk.Button(SettingPage, text = "Register", font = ('Consolas', 16), width = 1, height = 1, fg = '#000000', command = regface, bg = '#668db2')
RegisterFaceButton.grid(row = 10, column = 36, columnspan = 8, rowspan = 2, sticky = "NSEW")
ChangePinButton = tk.Button(SettingPage, text = "Change", font = ('Consolas', 16), width = 1, height = 1, fg = '#000000', command = changepin, bg = '#668db2')
ChangePinButton.grid(row = 13, column = 20, columnspan = 8, rowspan = 2, sticky = "NSEW")
DisarmedStateButton = tk.Button(SettingPage, text = "Disarmed", font = ('Consolas', 16), width = 1, height = 1, fg = '#000000', command = disarmedstate, bg = '#668db2')
DisarmedStateButton.grid(row = 10, column = 4, columnspan = 8, rowspan = 2, sticky = "NSEW")
HomeStateButton = tk.Button(SettingPage, text = "Home ", font = ('Consolas', 16), width = 1, height = 1, fg = '#000000', command = homestate, bg = '#668db2')
HomeStateButton.grid(row = 13, column = 4, columnspan = 8, rowspan = 2, sticky = "NSEW")
AwayStateButton = tk.Button(SettingPage, text = "Away", font = ('Consolas', 16), width = 1, height = 1, fg = '#000000', command = awaystate, bg = '#668db2')
AwayStateButton.grid(row = 16, column = 4, columnspan = 8, rowspan = 2, sticky = "NSEW")


# Hide the second window initially
SettingPage.withdraw()


# Poppup tkinter window
def create_pin_popup():
    # Create a new Tkinter window for the PIN popup
    pin_window = tk.Toplevel()
    pin_window.title("Enter PIN")

    # Function to validate the entered PIN
    def validate_pin():
        entered_pin = pin_entry.get()
        if entered_pin == "1234":  # Replace "1234" with your desired PIN
            print("PIN entered successfully!")
            pin_window.destroy()  # Close the PIN popup window
        else:
            print("Incorrect PIN!")
    
    # Label and entry widget for entering the PIN
    pin_label = tk.Label(pin_window, text="Enter PIN:")
    pin_label.pack()

    pin_entry = tk.Entry(pin_window, show="*")  # Use "*" to hide the PIN characters
    pin_entry.pack()

    # Button to submit the PIN
    submit_button = tk.Button(pin_window, text="Submit", command=validate_pin)
    submit_button.pack()
    
    
# Serial communication =====================================================================================================
ser = serial.Serial("/dev/ttyACM0", 9600, timeout = 1)
ser.flush()

def received_serial_command(command):
    if command[0] == 'p':
        if command[1] == 'y':
            open_SettingPage()
        elif command[1] == 'n':
            messagebox.showerror("Error", "Incorrect PIN!")
            
    if command[0] == 'f':
        face = "f" + face_match + "\n"
        ser.write(face.encode('utf-8'))
        
    if command[0] == 'x':
        m_state = int(command[1])
        # m_state = int(command[2])
        p_state = int(command[3])
        s_state = int(command[4])
        display_state()
        

    
# Facial recognition code ==================================================================================================
# Load the pre-trained face detection model
face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')

cap = cv2.VideoCapture(0, cv2.CAP_DSHOW)

cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)

counter = 0

face_match = "f"
face_detected = False

folder_path = Path("/home/willnatsan/uni/acs233-burglar-alarm/pics")


# Face functions
def detect_faces(frame):
    # Convert the frame to grayscale
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    
    # Detect faces in the grayscale image
    faces = face_cascade.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=5, minSize=(30, 30))
    
    # Return True if at least one face is detected, False otherwise
    return len(faces) > 0

def check_face(frame):
    global face_match
    if face_detected:
        try:
            for file_path in folder_path.iterdir():
                if file_path.is_file():
                    refrence_img = cv2.imread(file_path)
                    if DeepFace.verify(frame, refrence_img.copy())['verified']:
                        face_match = "y"
                        break
            else:
                face_match = "n"
        except ValueError:
            face_match = "f"
    else:
        face_match = "f"
        
        
# Main Loop ================================================================================================================
while loop:
    # serial
    if ser.in_waiting > 0:
        line = ser.readline().decode('utf-8').strip()
        print(line)
        
        received_serial_command(line)
    
    
    # Running tkinter window
    try:
        PinPage.update()  # Manually update the application
    except tk.TclError:
        break  # Exit the loop if the main window is closed


    # Running facial recognition
    ret, frame = cap.read()
    
    if ret:
        if counter % 30 == 0:
            face_detected = detect_faces(frame)
            try:
                threading.Thread(target=check_face, args=(frame.copy(),)).start()
            except ValueError:
                pass
            counter = 0
        
        counter += 1
        
        if face_match == "y":
            cv2.putText(frame, "MATCH!", (20, 450), cv2.FONT_HERSHEY_SIMPLEX, 2, (0, 255, 0), 3)
        elif face_match == "n":
            cv2.putText(frame, "NO MATCH!", (20, 450), cv2.FONT_HERSHEY_SIMPLEX, 2, (0, 0, 255), 3)
        elif face_match == "f":
            cv2.putText(frame, "NO Face!", (20, 450), cv2.FONT_HERSHEY_SIMPLEX, 2, (0, 0, 255), 3)

        cv2.imshow("video", frame)
        
        
    # Break out of while loop when 'q' is pressed
    key = cv2.waitKey(1)
    if key == ord("q"):
        loop = False
    

# Closs all open windows
PinPage.destroy()
cap.release()
cv2.destroyAllWindows()    