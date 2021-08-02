public class Base32 {
    public Base32() {

    }

    static final String symOfBase32="0123456789ABCDEFGHJKMNPQRSTVWXYZ";


    /**
     * 简单判断一个字符串是否满足32进制要求
     */
    public static int Base32Legality(String rs)throws MyException{
        int len=rs.length();

            for(int i=0;i<len;i++){
                char temp=rs.charAt(i);
                temp=Character.toUpperCase(temp);
                if(symOfBase32.indexOf(temp)!=-1)
                    continue;
                else
                    throw new MyException("Base32不合规-CCCode包含无效字符'"+temp+"'");
            }
        return 0;//合法
    }

    /**
     * 10进制数转换为32进制数
     * @param num
     * @return
     */
    public static String Dec2Base32(int num)throws MyException{
        String res=new String();

            if(num<0)throw new MyException("Base32不合规-转换数字不能是负数");


            while(num>=32){
                int temp=num%32;
                char c=symOfBase32.charAt(temp);
                res=c+res;
                num/=32;
            }
            res=symOfBase32.charAt(num)+res;


        return res;
    }
}

