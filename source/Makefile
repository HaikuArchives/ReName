EXECUTABLE = ReName

HDRS =	Application.h\
  			AppDefs.h\
  			AppWindow.h\
  			DragDropView.h\
  			FileName.h\
			List.h\
  			RenameView.h

SRCS =	driver.cpp\
			Application.cpp\
  			AppWindow.cpp\
  			DragDropView.cpp\
  			FileName.cpp\
			List.cpp\
  			RenameView.cpp

OBJS = $(SRCS:.cpp=.o)

RSRCS =ReName.rsrc


LIBS = -lbe -lroot

CC = g++
CFLAGS = -DDEBUG -g
LD = g++
LDFLAGS = -Xlinker
XRES = xres
MIMESET = mimeset

$(EXECUTABLE) : $(OBJS)
	$(LD) -o $(EXECUTABLE) $(OBJS) $(LDFLAGS) $(LIBS)
	$(XRES) -o ""$(EXECUTABLE)"" $(RSRCS)
	$(MIMESET) -f "$(EXECUTABLE)"
	chmod 755 $(EXECUTABLE)

clean  :
	rm -f *.o $(EXECUTABLE)

install : $(EXECUTABLE)
	copyattr --data -- $(EXECUTABLE) ..

cleaninstall : clean
	rm -f ../$(EXECUTABLE)

release : CFLAGS = -O3
release : cleaninstall install
	make clean

%.o : %.cpp
	$(CC) -c $< $(CFLAGS) -o $@
