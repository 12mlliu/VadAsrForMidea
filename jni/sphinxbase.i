/*sphinxbase.i by meili 
2017/01/06*/

%define DOCSTRING
"This documentation was automatically generated using original comments in
Doxygen format. As some C types and data structures cannot be directly mapped
into Python types, some non-trivial type conversion could have place.
Basically a type is replaced with another one that has the closest match, and
sometimes one argument of generated function comprises several arguments of the
original function (usually two).

Functions having error code as the return value and returning effective
value in one of its arguments are transformed so that the effective value is
returned in a regular fashion and run-time exception is being thrown in case of
negative error code."
%enddef

%module SphinxBase
%rename("%(lowercamelcase)s", notregexmatch$name="^[A-Z]") "";

%feature("autodoc", "1");

%include typemaps.i
%include iterators.i

%begin %{

#ifndef __cplusplus
typedef int bool;
#define true 1
#define false 0
#endif

#include <sphinxbase/cmd_ln.h>
#include <sphinxbase/err.h>
#include <pocketsphinx.h>
typedef cmd_ln_t Config;
%}

/*don't want swig to creat default constructors for our own config
because our config didn't like others
no first step (malloc?),only free */
%nodefaultctor Config;

typedef struct {} Config;

%extend Config {

    Config(){
        Config *c = cmd_ln_parse_r(NULL,ps_args(),0,NULL,FALSE);
        return c;
    }
    ~Config() {
        cmd_ln_free_r($self);
    }

    /*set a string in a command_line object*/
    void set_string(const char *key, const char *val) {
        cmd_ln_set_str_r($self, key, val);
    }
    void set_float(const char *key,double val){
        cmd_ln_set_float_r($self,key,val);
    }
}
