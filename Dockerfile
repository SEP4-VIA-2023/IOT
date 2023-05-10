FROM alpine:3.14

# Update apk
RUN apk update

# Install python3 for platformio
RUN apk add --no-cache python3 py3-pip py3-virtualenv

# Install platformio
RUN wget https://raw.githubusercontent.com/platformio/platformio-core-installer/master/get-platformio.py \
    && python3 get-platformio.py \
    && rm get-platformio.py

# Reload udev rules
RUN udevadm control --reload-rules && udevadm trigger

# Set PATH environment variable
ENV PATH "$PATH:/root/.local/bin"
