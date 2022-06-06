#clarionInterface.thrift

service clarionInterface_IDLserver
{
    /** 
    * Quite the module
    * terminates the module and rpc server
    **/
    bool quit();

    /**
    * Points at coordinates
    * returns when action is complete
    **/
    bool point(1:double pos_x, 2:double pos_y, 3:double pos_z)
}