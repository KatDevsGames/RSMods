using System;
using System.Diagnostics;
using System.IO;
using System.Windows.Forms;

namespace RS2014_Mod_Installer
{
    class Worker
    {
        public static string WhereIsRocksmith()
        {
            return RSMods.Util.GenUtil.GetRSDirectory();
        }
    }
    class DLLStuff
    {
        public static void InjectDLL(string rocksmithLocation)
        {
            File.WriteAllBytes(Path.Combine(@rocksmithLocation, "D3DX9_42.dll"), Properties.Resources.D3DX9_42);
            if (MessageBox.Show("Do you own the Cherub Rock DLC for Rocksmith 2014? It is needed to play cDLC out of the box.", "Quick Question", MessageBoxButtons.YesNo, MessageBoxIcon.Information) == DialogResult.No)
                if (MessageBox.Show("Would you like us to bring you to the purchase page of the DLC. It is normally $2.99 USD but regularly goes on sale for $1.79 USD", "Want to purchase Cherub Rock?", MessageBoxButtons.YesNo, MessageBoxIcon.Information) == DialogResult.Yes)
                    Process.Start("https://store.steampowered.com/app/248750/");
            MessageBox.Show("You can now play cDLC. Have fun, and don't forget to rock out!");
            Environment.Exit(1);
        }
    }
} 
