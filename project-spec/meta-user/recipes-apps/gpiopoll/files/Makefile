APP = gpiopoll

# Add any other object files to this list below
APP_OBJS = gpiopoll.o
CFLAGS += -g -Wall

all: build

build: $(APP)

$(APP): $(APP_OBJS)
	$(CC) $(LDFLAGS) -o $@ $(APP_OBJS) $(LDLIBS)

clean:
	rm -f $(APP_OBJS) $(APP)

