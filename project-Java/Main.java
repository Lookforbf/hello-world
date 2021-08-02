import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) {

        BufferedReader br = new BufferedReader( new
                InputStreamReader(System.in));
        System.out.println("*** CCCode计算与验证系统 ***");
        System.out.println("* 主菜单：输入数字进入相应模式");
        System.out.println("1:验证码计算模式");
        System.out.println("2:CCCode验证模式");
        try {
            String line=br.readLine();
            while (line!="Q"||line!="q") {



                if(line.equals("1")){
                    calculateCheckCodeMode();
                }else if(line.equals("2")){
                    verifyCCCodeMode();
                }else{
                    System.out.println("请重新输入");
                }
                System.out.println("* 主菜单：输入数字选择你要进入的模式");
                line=br.readLine();


            }
            System.out.println("程序退出。");
        } catch (Exception e) {
            System.out.println(e.getMessage());
            e.printStackTrace();
        }

    }

    /**
     * 计算校验码用户交互
     * @throws Exception
     */
    public static void calculateCheckCodeMode()throws Exception{
        System.out.println("> 你已进入计算校验码模式");
        System.out.println("> 请输入标准格式CCCode进行验证");
        BufferedReader br = new BufferedReader( new
                InputStreamReader(System.in));
        String line=br.readLine();
        while (!line.equals("q")){
            try{

                line=StringManip.RemoveSeparator(line);//分隔符数量不限制
                char t=SystemI.calculateCheckCode(line);
                System.out.println("生成的完整CCCode为："+StringManip.AddSeparator(line+t));


            }catch (MyException e){
                System.out.println(e.getMessage());

            }finally {
                line=br.readLine();
            }
        }
        System.out.println("退出当前模式");

    }
    public static void verifyCCCodeMode()throws Exception{
        System.out.println("> 你已进入验证CCCode模式");
        System.out.println("> 请输入标准格式CCCode进行验证");
        BufferedReader br = new BufferedReader( new
                InputStreamReader(System.in));
        String line=br.readLine();
        while (!line.equals("q")){
            try {
                if (SystemI.verifyCC(line)) {
                    System.out.println("验证通过");
                } else {
                    System.out.println("验证失败");
                }
            }catch (MyException e){
                System.out.println(e.getMessage());
            }finally {
                line=br.readLine();
            }
        }
        System.out.println("退出当前模式");
    }
}
