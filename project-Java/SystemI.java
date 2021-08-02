public class SystemI {
    final static int WEIGHT = 7;
    public static char calculateCheckCode(String CC_)throws MyException{

        if (StringManip.isDataLegal(CC_ + "0")) {//插入默认数字0,只能是0，后面计算会用到
            String CC = StringManip.RemoveSeparator(CC_+"0");//保险起见
            int sum = 0;
            for (int i = 0; i < CC.length(); i++) {
                if (i % 2 == 0) {
                    sum += Base32.symOfBase32.indexOf(CC.substring(i, i + 1)) * WEIGHT;
                } else {
                    sum += Base32.symOfBase32.indexOf(CC.substring(i, i + 1));
                }
            }
            sum %= 32;
            return Base32.symOfBase32.charAt((32 - sum)%32);
        } else {
            throw new MyException("待检验字符串不符合长度规范或格式规范-calculateCheckCode");
        }

    }

    public static boolean verifyCC(String CC)throws MyException{
        if(StringManip.isDataLegal(CC)){
            char checkcode=calculateCheckCode(CC.substring(0,CC.length()-1));
            if(checkcode-CC.charAt(CC.length()-1)==0)return true;
            else {
                System.out.println("正确字符应为："+checkcode);
                return false;
            }
        }else{
            throw new MyException("待检验字符串不符合长度规范或格式规范-verifyCC");
        }
    }
}
