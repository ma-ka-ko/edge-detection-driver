.PHONY: clean_dependencies
CPPFLAGS += -g -D DEBUG  
CPPFLAGS += -D_LINUX -fpic 
CXXFLAGS += -std=c++0x 
#CXXFLAGS += -Wno-deprecated


CPPFLAGS += -Wall -Wextra -Wformat-nonliteral -Wformat-security 
CPPFLAGS += -Wchar-subscripts \
             -Wcomment \
             -Werror
#CPPFLAGS += -Wlogical-op
#CPPFLAGS += -Wshadow
#CPPFLAGS += -Waggregate-return
CPPFLAGS += -Wcast-qual
CPPFLAGS += -Wwrite-strings

# Change how .cc files are compiled in order to generate header dependancies.
# Details about this method are available at http://make.paulandlesley.org/autodep.html

%.o : %.cpp
#	echo $(COMPILE.cpp) -MD -o $@ $<
	$(COMPILE.cpp) -MD -o $@ $<
	@cp $*.d $*.P; \
	sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
	-e '/^$$/ d' -e 's/$$/ :/' < $*.d >> $*.P; \
	rm -f $*.d

-include $(SRCS:%.cpp=%.P)


clean::
	@rm -vf *.P
	@rm -vf *.o
	@rm -vf *.d
	@rm -vf $(OBJS)

