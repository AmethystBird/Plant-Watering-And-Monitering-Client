import time
from azure.iot.device import IoTHubDeviceClient

#CONNECTION_STRING = "HostName=PlantSensorHub.azure-devices.net;DeviceId=PlantSensorNucleoBoard;SharedAccessKey=4/easOmixo7XFH1QhgPiZLXWKqNThX1ZpA+rGUakszQ=" #Board Primary
CONNECTION_STRING = "HostName=PlantSensorHub.azure-devices.net;DeviceId=PythonSensorReceiverClient;SharedAccessKey=q/LCQCIaNAgLahucHJ9Qx12g4/dgoCZucBAsBycyin0=" #Receiver Primary
#CONNECTION_STRING = "HostName=iotc-c2dd98d8-fcdb-485c-9f10-9f15250ad05a.azure-devices.net;DeviceId=1ihhjwmthyh;SharedAccessKey=V+r5zstilUDIZVSp9qmO89Mn1l8u9sK4EhRQUZhpHoA=" #Central
#CONNECTION_STRING = "HostName=PlantSensorHub.azure-devices.net;SharedAccessKeyName=service;SharedAccessKey=t0UsaTv1beO9cF9obQXYHO5UrA1ffGaHGR+bz8vd+wo=" #service
#CONNECTION_STRING = "HostName=PlantSensorHub.azure-devices.net;SharedAccessKeyName=iothubowner;SharedAccessKey=C9x3JOrLzFwfMLYTI+BA0uHmSfga/Oh18IoOxgcqJJQ=" #iothubowner
#CONNECTION_STRING = "HostName=PlantSensorHub.azure-devices.net;SharedAccessKeyName=device;SharedAccessKey=393jckrInx/tLvP0caKgQWEdGQq9q07yTiz71kXIDHo=" #device
RECEIVED_MESSAGES = 0
#DeviceId = "PlantSensorNucleoBoard"

def message_handler(message):
    global RECEIVED_MESSAGES
    RECEIVED_MESSAGES += 1
    print("")
    print("Message received:")

    # print data from both system and application (custom) properties
    for property in vars(message).items():
        print ("    {}".format(property))

    print("Total calls received: {}".format(RECEIVED_MESSAGES))

def main():
    print ("Starting the Python IoT Hub C2D Messaging device sample...")

    # Instantiate the client
    client = IoTHubDeviceClient.create_from_connection_string(CONNECTION_STRING)

    print ("Waiting for C2D messages, press Ctrl-C to exit")
    try:
        # Attach the handler to the client
        client.on_message_received = message_handler

        while True:
            time.sleep(1000)
    except KeyboardInterrupt:
        print("IoT Hub C2D Messaging device sample stopped")
    finally:
        # Graceful exit
        print("Shutting down IoT Hub Client")
        client.shutdown()

if __name__ == '__main__':
    main()

#IOTHUB_DEVICE_SECURITY_TYPE = "CONNECTION_STRING"
#EVENT_HUB_CONSUMER_GROUP = "<event_hub_name>"

#def create_client():
    # Instantiate the client
#    client = IoTHubDeviceClient.create_from_connection_string(CONNECTION_STRING)

    # Define the handler for method requests
#    def method_request_handler(method_request):
#        if method_request.name == "rebootDevice":
            # Act on the method by rebooting the device
#            print("Rebooting device")
#            time.sleep(20)
#            print("Device rebooted")

            # ...and patching the reported properties
#            current_time = str(datetime.datetime.now())
#            reported_props = {"rebootTime": current_time}
#            client.patch_twin_reported_properties(reported_props)
#            print( "Device twins updated with latest rebootTime")

            # Create a method response indicating the method request was resolved
#            resp_status = 200
#            resp_payload = {"Response": "This is the response from the device"}
#            method_response = MethodResponse(method_request.request_id, resp_status, resp_payload)

#        else:
            # Create a method response indicating the method request was for an unknown method
#            resp_status = 404
#            resp_payload = {"Response": "Unknown method"}
#            method_response = MethodResponse(method_request.request_id, resp_status, resp_payload)

        # Send the method response
#        client.send_method_response(method_response)

#    try:
        # Attach the handler to the client
#        client.on_method_request_received = method_request_handler
#    except:
        # In the event of failure, clean up
#        client.shutdown()

#    return client

#def main():
#    print ("Starting the IoT Hub Python sample...")
#    client = create_client()

#    print ("Waiting for commands, press Ctrl-C to exit")
#    try:
        # Wait for program exit
#        while True:
#            time.sleep(1000)
#    except KeyboardInterrupt:
#        print("IoTHubDeviceClient sample stopped")
#    finally:
        # Graceful exit
#        print("Shutting down IoT Hub Client")
#        client.shutdown()