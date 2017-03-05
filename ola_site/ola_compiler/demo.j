.class public demo
.super java/lang/Object
.field public static _sc Ljava/util/Scanner;
.method public static main([Ljava/lang/String;)V
.limit stack 20  ;
.limit locals 20
new java/util/Scanner
dup
getstatic java/lang/System/in Ljava/io/InputStream;
invokespecial java/util/Scanner/<init>(Ljava/io/InputStream;)V
putstatic demo/_sc Ljava/util/Scanner;
getstatic java/lang/System/out Ljava/io/PrintStream;
ldc "Hello World!"
invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
    return
.end method
