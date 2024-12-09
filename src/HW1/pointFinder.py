import cv2

def click_event(event, x, y, flags, param):
    if event == cv2.EVENT_LBUTTONDOWN:
        # Get the dimensions of the image
        height, width, _ = param.shape
        
        # Convert x and y to the range of -1 to 1 with center as (0, 0)
        x_normalized = (x / (width / 2)) - 1
        y_normalized = 1 - (y / (height / 2))
        
        print(f"Clicked at: ({x_normalized}, {y_normalized})")

# Load the image
image_path = 'D:\\FH Uni\\rtg\\Exercise1-Draw2DScene-VBOVAO\\src\\HW1\\sample.jpg'
image = cv2.imread(image_path)

# Check if the image was loaded successfully
if image is None:
    print("Error: Could not load image. Please check the file path.")
else:
    # Display the image
    cv2.imshow('Image', image)

    # Set mouse callback function to capture click events
    cv2.setMouseCallback('Image', click_event, image)

    # Wait until a key is pressed
    cv2.waitKey(0)

    # Destroy all windows
    cv2.destroyAllWindows()