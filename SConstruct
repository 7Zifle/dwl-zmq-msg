from SCons import __version__ as scons_raw_version
# Gets the standard flags CC, CCX, etc.
env = DefaultEnvironment()

scons_ver = env._get_major_minor_revision(scons_raw_version)
if scons_ver >= (4, 0, 0):
  env.Tool("compilation_db")
  cdb = env.CompilationDatabase()
  env.Alias("compiledb", cdb)
  Default(cdb)

prog = env.Program('dwl-msg.c', LIBS=["zmq", "czmq"])
Default(prog)


